/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package concurrentlinkedlist;

import java.util.Random;

/**
 *
 * @author carlosv
 */
public class ConcurrentLinkedListDriver {
    
    private static final int MAX_VALUE = 10;
    private static final int OPERATIONS = 100;
    
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        Random randomGenerator = new Random();
        ConcurrentLinkedList list = new ConcurrentLinkedList();
        for (int i = 0; i < OPERATIONS; ++i) {
            int value = randomGenerator.nextInt(2*MAX_VALUE+1) - MAX_VALUE;
            Node n = new Node(value);
            // operate with list and n
        }
        
    }
}
