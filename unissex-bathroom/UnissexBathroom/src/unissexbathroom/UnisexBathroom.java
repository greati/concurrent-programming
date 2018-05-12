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
     * 
     * 
     */
    int headQueue = 0;
    
    /**
     * The bathroom.
     */
    final private List<Person> bathroom;
    
    /**
     * Lock for providing condition variables.
     * 
     */
    final Lock lock = new ReentrantLock(true);
    
    /**
     * Condition variable for indicating emptiness.
     * 
     */
    final Condition empty = lock.newCondition();
    
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
    public void insert(Person p) {
        lock.lock();
        try {
            
            if (p.getId() != this.headQueue)
                this.queue.await();
                        
            if (this.bathroom.size() == this.maxCapacity) {
                System.out.println("Awaiting full: " + p);
                full.await();
            }

            if (!this.bathroom.isEmpty()) {
                Person.Gender currentGender = this.bathroom.get(0).getGender();
                
                if (currentGender == Person.Gender.LADY && p.getGender() == Person.Gender.GENTLEMAN) {
                    System.out.println("Awaiting gender: " + p);
                    this.gentlemenIn.await();
                }
                else if (currentGender == Person.Gender.GENTLEMAN && p.getGender() == Person.Gender.LADY) {
                    System.out.println("Awaiting gender: " + p);
                    this.ladiesIn.await();
                }
            }
            
            synchronized(this) {
                this.bathroom.add(p);
                this.headQueue++;
                queue.signal();
            }
                        
            System.out.println("==> " + p + "\n(!) Current: " + this.bathroom.size() + "/" + this.maxCapacity + "\n");
            
            if (this.bathroom.size() == 1) {         
                // Since will
                empty.signal();
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
    public void remove(Person p) {
        lock.lock();
        try {
            if (this.bathroom.isEmpty()) {
                empty.await();
            }
            
            synchronized(this){
                this.bathroom.remove(p);
            }
            
            System.out.println("<== " + p + "\n(!) Current: " + this.bathroom.size() + "\n");
            
            if (this.bathroom.size() == this.maxCapacity - 1) 
                full.signal();
            
            if (this.bathroom.isEmpty()) {
                // Gender
                switch (p.getGender()) {
                    case GENTLEMAN:
                        System.out.println("Signal ladies");
                        this.ladiesIn.signal();
                        break;
                    case LADY:
                        System.out.println("Signal gentleman");
                        this.gentlemenIn.signal();
                        break;
                }
            }
            
        } catch(InterruptedException e) {
        
        } finally {            
            lock.unlock();
        }        
    }
}
