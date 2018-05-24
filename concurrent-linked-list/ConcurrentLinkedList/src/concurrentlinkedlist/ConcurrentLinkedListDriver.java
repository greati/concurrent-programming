/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package concurrentlinkedlist;

import concurrentlinkedlist.Operation.OpType;
import java.util.Random;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author carlosv
 */
public class ConcurrentLinkedListDriver {
    
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        ConcurrentLinkedList l1 = new ConcurrentLinkedList();
        
        Random randomGenerator = new Random();
        
        int ordGenerator = 0;
        
        while (true) {
            try {        
                
                int operation = randomGenerator.nextInt(3);
                
                Operation.OpType op = null;
                switch (operation) {
                    case 0: op = OpType.INSERT;
                    case 1: op = OpType.REMOVE;
                    case 2: op = OpType.SEARCH;
                }
                
                Thread t = new Operation(ordGenerator++, op ,l1);
                
                t.setDaemon(true);
                t.start();
                
                Thread.sleep(500);
            } catch (InterruptedException ex) {
                Logger.getLogger(ConcurrentLinkedListDriver.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
        
    }
}
