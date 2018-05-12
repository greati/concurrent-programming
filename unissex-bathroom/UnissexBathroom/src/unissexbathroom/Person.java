/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package unissexbathroom;

/**
 * Represents a person.
 * 
 * @author vitorgreati
 */
class Person {
    
    /**
     * Possible genders of a person, well named.
     */
    enum Gender {
        LADY,
        GENTLEMAN 
    }
    
    /**
     * Person's identifier.
     * 
     */
    private int id;
    
    /**
     * The gender of the person.
     */
    private Gender gender;
    
    
    /**
     * Public constructor.
     * 
     */
    public Person(int id, Gender gender) {
        this.id = id;
        this.gender = gender;
    }
    
    /**
     * String representation.
     * 
     * @return The string representation.
     */
    @Override
    public String toString() {
        return    "Id: " + String.valueOf(id) + " // "
                + "Gender: " + String.valueOf(gender);
    }

    /**
     * Hash representation.
     * 
     * @return 
     */
    @Override
    public int hashCode() {
        int hash = 3;
        hash = 67 * hash + this.id;
        return hash;
    }

    /**
     * Equality.
     * 
     * @param obj
     * @return 
     */
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
        final Person other = (Person) obj;
        return this.id == other.id;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public Gender getGender() {
        return gender;
    }

    public void setGender(Gender gender) {
        this.gender = gender;
    }
    
}
