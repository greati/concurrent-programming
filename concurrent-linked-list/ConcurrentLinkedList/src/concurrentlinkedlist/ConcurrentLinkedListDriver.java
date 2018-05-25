/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package concurrentlinkedlist;

import concurrentlinkedlist.ListUser.Operation;
import java.util.Random;

/**
 *
 * @author carlosv
 */
public class ConcurrentLinkedListDriver {
    private static final int OPERATIONS = 5;
    public static final Random RANDOM_GEN = new Random();
    private static final int MAX_VALUE = 5;
   
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        ConcurrentLinkedList list = new ConcurrentLinkedList();
        for (int i = -MAX_VALUE; i <= MAX_VALUE; ++i) {
            list.insert(i, true);
        }
        System.out.println(list);
        
        for (int i = 0; i < OPERATIONS; ++i) {
            int value = RANDOM_GEN.nextInt(2*MAX_VALUE+1) - MAX_VALUE;
            
            int op_num = RANDOM_GEN.nextInt(3);
            Operation op;
            switch(op_num) {
                case 1:
                    op = Operation.INSERTION;
                    break;
                case 2:
                    op = Operation.REMOVAL;
                    break;
                default:
                    op = Operation.SEARCH;
                    break;
            }
            ListUser user = new ListUser(list, op, value);
            user.start();
        }
        
    }
}
