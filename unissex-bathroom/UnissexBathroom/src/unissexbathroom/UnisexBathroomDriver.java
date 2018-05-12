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
     * @param args the command line arguments
     */
    public static void main(String[] args) {

        //UnisexBathroom bathroom = new UnisexBathroom(Integer.valueOf(args[0]));
        UnisexBathroom bathroom = new UnisexBathroom(5);

        
        Random randomGenerator = new Random();
        
        int idGenerator = 0;
        
        // Generate bathroom users
        while (true) {
            try {
                // Choose gender randomly
                int genderRandInt = randomGenerator.nextInt(2);
                Person.Gender gender =  (genderRandInt == 0) ? Person.Gender.GENTLEMAN : Person.Gender.LADY;
                
                // Choose time randomly
                int timeRandInt = 2000 + randomGenerator.nextInt(2000);
                
                BathroomUser user = new BathroomUser(new Person(idGenerator++, gender), bathroom, timeRandInt);
                
                user.setDaemon(true);
                user.start();
                
                Thread.sleep(500); 
            } catch (InterruptedException ex) {
                Logger.getLogger(UnisexBathroomDriver.class.getName()).log(Level.SEVERE, null, ex);
            }
        }

    }
    
}
