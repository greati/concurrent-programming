/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package unissexbathroom;

import java.util.Random;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author vitorgreati
 */
public class UnisexBathroomDriver {

    /**
     * Driver for testing the unisex bathroom implementation.
     * 
     * It generates a bathroom user of a random gender and with a random
     * time to spent inside the bathroom (in the interval [2000 ms,4000 ms]).
     * 
     * @param args the command line arguments
     */
    public static void main(String[] args) {

        UnisexBathroom bathroom = new UnisexBathroom(Integer.valueOf(args[0]));

        Random randomGenerator = new Random();
        
        int orderGenerator = 1;
        
        // Generate bathroom users
        while (true) {
            try {
                // Choose gender randomly
                int genderRandInt = randomGenerator.nextInt(2);
                BathroomUser.Gender gender =  (genderRandInt == 0) ? BathroomUser.Gender.GENTLEMAN : BathroomUser.Gender.LADY;
                
                // Choose time randomly
                int timeRandInt = 2000 + randomGenerator.nextInt(2000);
                
                BathroomUser user = new BathroomUser(gender, bathroom, timeRandInt, orderGenerator++);
                
                user.setDaemon(true);
                user.start();
                
                Thread.sleep(1000); 
            } catch (InterruptedException ex) {
                Logger.getLogger(UnisexBathroomDriver.class.getName()).log(Level.SEVERE, null, ex);
            }
        }

    }
    
}
