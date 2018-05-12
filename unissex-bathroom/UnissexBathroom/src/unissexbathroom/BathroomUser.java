/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package unissexbathroom;

import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author vitorgreati
 */
public class BathroomUser extends Thread {
    
    /**
     * Possible genders of a person, well named.
     */
    public enum Gender {
        LADY,
        GENTLEMAN 
    }
    
    /**
     * The gender of the person.
     */
    private final Gender gender;
    
    /**
     * Bathroom.
     * 
     */
    final private UnisexBathroom bathroom;
    
    /**
     * Time to spend.
     * 
     */
    final private int timeToSpend;
    
    /**
     * Order of approach.
     * 
     */
    final private int order;
    
    /**
     * Constructor.
     * 
     * @param gender
     * @param bathroom
     * @param order
     * @param timeToSpend
     */
    public BathroomUser(Gender gender, UnisexBathroom bathroom, int timeToSpend, int order) {
        this.gender = gender;
        this.bathroom = bathroom;
        this.timeToSpend = timeToSpend;
        this.order = order;
    }
    
    /**
     * Run thread.
     * 
     */
    @Override
    public void run() {
        try {
                        
            this.bathroom.insert(this);
            
            Thread.sleep(timeToSpend);
            
            this.bathroom.remove(this);
            
        } catch (InterruptedException ex) {
            Logger.getLogger(BathroomUser.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    public UnisexBathroom getBathroom() {
        return bathroom;
    }

    public int getTimeToSpend() {
        return timeToSpend;
    }

    public int getOrder() {
        return order;
    }

    public Gender getGender() {
        return gender;
    }

    @Override
    public int hashCode() {
        int hash = 7;
        hash = 41 * hash + this.order;
        return hash;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) {
            return true;
        }
        if (obj == null) {
            return false;
        }
        if (getClass() != obj.getClass()) {
            return false;
        }
        final BathroomUser other = (BathroomUser) obj;
        return this.order == other.order;
    }

    @Override
    public String toString() {
        return this.gender + " " + this.order;
    }   
    
}
