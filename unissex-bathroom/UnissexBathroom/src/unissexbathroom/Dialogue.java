/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package unissexbathroom;

import java.util.List;

/**
 * Class to allow printing messages about the bathroom usage.
 * 
 * @author vitorgreati
 */
public class Dialogue {
    
    /**
     * Represents a person talk.
     * 
     * @param person
     * @param talk 
     */
    public static void talk (BathroomUser person, String talk) {
        System.out.println(person + " says: " + talk+"\n");
    }
    
    /**
     * Represents a narrator speech.
     * 
     * @param text 
     */
    public static void narrate (String text) {
        System.out.println("(" + text + ")" + "\n");
    }
    
    /**
     * Correctly prints the number of persons of a gender.
     * 
     * @param bathroom
     * @return 
     */
    public static String quantityGender (List<BathroomUser> bathroom) {
        return (bathroom.isEmpty() ? "nobody" : bathroom.size() == 1 ? "1 " + 
            pluralGender(bathroom.size(), bathroom.get(0).getGender()) : 
            bathroom.size() + " " + pluralGender(bathroom.size(), bathroom.get(0).getGender()));
    }
    
    /**
     * Correctly print the number of people in the queue.
     * 
     * @param orderNumber
     * @param currentHeadQueue
     * @return 
     */
    public static String quantityInTheQueue (int orderNumber, int currentHeadQueue) {
        int quantity = (orderNumber - currentHeadQueue);
        return (quantity == 0 ? "nobody" : String.valueOf(quantity));
    }
    
    /**
     * Correctly prints the plural of a gender.
     * 
     * @param quantity
     * @param gender
     * @return 
     */
    public static String pluralGender (int quantity, BathroomUser.Gender gender) {
        if (quantity == 0) return "nobody";
        
        switch(gender) {
            case GENTLEMAN:
                return (quantity == 1 ? "gentleman" : "gentlemen");
                
            case LADY:
                return (quantity == 1 ? "lady" : "ladies");
                
            default:
                return "unknown";
        }
    }
    
    /**
     * Correctly print the plural of person.
     * 
     * @param quantity
     * @return 
     */
    public static String pluralPerson (int quantity) {
        if (quantity == 0) return "";
        return (quantity == 1 ? " person" : " people");
    }
}
