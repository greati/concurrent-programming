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
     * Person.
     * 
     */
    final private Person user;
    
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
     * Constructor.
     * 
     * @param user
     * @param bathroom
     * @param timeToSpend
     */
    public BathroomUser(Person user, UnisexBathroom bathroom, int timeToSpend) {
        this.user = user;
        this.bathroom = bathroom;
        this.timeToSpend = timeToSpend;
    }
    
    /**
     * Run thread.
     * 
     */
    @Override
    public void run() {
        try {
            
            System.out.println("==?> " + this.user + " (" + this.timeToSpend + ")" + "\n");
            
            this.bathroom.insert(this.user);
            
            Thread.sleep(timeToSpend);
            
            this.bathroom.remove(this.user);
            
        } catch (InterruptedException ex) {
            Logger.getLogger(BathroomUser.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    
}
