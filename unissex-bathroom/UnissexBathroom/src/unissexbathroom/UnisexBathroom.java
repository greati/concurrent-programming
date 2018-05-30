/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package unissexbathroom;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

/**
 * Monitor that represents an unisex bathroom, with the following rules:
 * <ul>
 *  <li>there is a maximum capacity, C, of people in the bathroom;</li>
 *  <li>there can be only people of one gender at a time;</li>
 *  <li>each person uses the bathroom for a certain amount of time;</li>
 *  <li>the outs and ins of people, as well as the amount of people inside at each time, must be shown;</li>
 * </ul>
 * 
 * @author vitorgreati
 */
public class UnisexBathroom {
 
    /**
     * Maximum capacity.
     * 
     */
    final int maxCapacity;
    
    /**
     * Current person in the head of the bathroom queue.
     * 
     */
    volatile int headQueue = 1;
    
    /**
     * The current bathroom state.
     */
    final private List<BathroomUser> bathroom;
    
    /**
     * Lock for providing condition variables.
     * 
     */
    final Lock lock = new ReentrantLock(true);
    
    /**
     * Condition variable for indicating fullness.
     * 
     */
    final Condition full = lock.newCondition();
    
    /**
     * Condition variable for indicating ladies in.
     * 
     */
    final Condition ladiesIn = lock.newCondition();
    
    /**
     * Condition variable for indicating gentleman in.
     * 
     */
    final Condition gentlemenIn = lock.newCondition();
    
    /**
     * Condition variable to enforce ordering.
     * 
     */
    final Condition queue = lock.newCondition();
    
    /**
     * Public constructor.
     * 
     * @param maxCapacity
     */
    public UnisexBathroom(int maxCapacity) {
        this.maxCapacity = maxCapacity;
        this.bathroom = new ArrayList<>();
    }
    
    /**
     * Insert a person into the bathroom.
     * 
     * @param p
     */
    public void insert(BathroomUser p) {
        lock.lock();
        try {
                        
            Dialogue.narrate(p + " arrived. " + "In the bathroom, " + Dialogue.quantityGender(this.bathroom) + ". " + 
                    "In the queue, "+ Dialogue.quantityInTheQueue(p.getOrder(), headQueue) +
                    Dialogue.pluralPerson(p.getOrder() - headQueue) + ".");
            
            if (p.getOrder() != this.headQueue) {
                Dialogue.talk(p, "Oh, no, a queue! I need to wait!");
                this.queue.await();
            }

            if (!this.bathroom.isEmpty()) {
                
                BathroomUser.Gender currentGender = this.bathroom.get(0).getGender();
                
                if (currentGender == BathroomUser.Gender.LADY && p.getGender() == BathroomUser.Gender.GENTLEMAN) {
                    Dialogue.talk(p, Dialogue.quantityGender(this.bathroom) + " in the bathroom! I need to wait.");
                    this.gentlemenIn.await();
                }
                else if (currentGender == BathroomUser.Gender.GENTLEMAN && p.getGender() == BathroomUser.Gender.LADY) {
                    Dialogue.talk(p, Dialogue.quantityGender(this.bathroom) + " in the bathroom! I need to wait.");
                    this.ladiesIn.await();
                }
                
                if (this.bathroom.size() == this.maxCapacity) {
                    Dialogue.talk(p, "The bathroom is full! Will I hold my fisiologic needs?!");
                    full.await();
                }
            }
            
            synchronized(this) {
                Dialogue.talk(p, "I can enter! Thank you, Universe!");
                this.bathroom.add(p);
                this.headQueue++;
                queue.signal();
            }
                        
        } catch(InterruptedException e) {
        
        }finally {            
            lock.unlock();
        }
    }
    
    /**
     * Remove person from the bathroom.
     * 
     * @param p
     */
    public void remove(BathroomUser p) {
        lock.lock();
        try {
            
            synchronized(this){
                this.bathroom.remove(p);
                Dialogue.narrate(p + " exits the bathroom.");
                Dialogue.talk(p, "What a good feeling! And it took only " + p.getTimeToSpend() + " ms! "
                        + "In the bathroom, " + 
                        (this.bathroom.isEmpty() ? "nobody" : this.bathroom.size() + " " + Dialogue.pluralGender(this.bathroom.size(), p.getGender())) + ".");
            }
                        
            if (this.bathroom.size() == this.maxCapacity - 1) 
                full.signal();
            
            if (this.bathroom.isEmpty()) {
                // Gender
                switch (p.getGender()) {
                    case GENTLEMAN:
                        this.ladiesIn.signal();
                        break;
                    case LADY:
                        this.gentlemenIn.signal();
                        break;
                }
            }            
        
        } finally {            
            lock.unlock();
        }        
    }
}
