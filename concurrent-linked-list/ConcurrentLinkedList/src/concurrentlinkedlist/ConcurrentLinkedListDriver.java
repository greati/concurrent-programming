/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package concurrentlinkedlist;

import java.util.ArrayList;
import concurrentlinkedlist.ListUser.Operation;
import java.util.Random;

/**
 *
 * @author carlosv
 */
public class ConcurrentLinkedListDriver {
    private static ConcurrentLinkedList list;
    public static final Random RANDOM_GEN = new Random();
    private static final int MAX_VALUE = 3;
    
    public static Operation randomOperation(boolean search, boolean insert,
            boolean remove) {
        ArrayList<Operation> options = new ArrayList<>();
        int n = 0;
        if (search) options.add(Operation.SEARCH);
        if (insert) options.add(Operation.INSERTION);
        if (remove) options.add(Operation.REMOVAL);
        
        int op_num = RANDOM_GEN.nextInt(options.size());
        return options.get(op_num);
    }
    
    public static void test(boolean search, boolean insert, boolean remove,
            int operations) {
        for (int i = 0; i < operations; ++i) {
            int value = RANDOM_GEN.nextInt(2*MAX_VALUE+1) - MAX_VALUE;
            
            Operation op = randomOperation(search, insert, remove);
            ListUser user = new ListUser(list, op, value);
            user.start();
        }
    }
   
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        list = new ConcurrentLinkedList();
        for (int i = -MAX_VALUE; i <= MAX_VALUE; ++i) {
            list.insert(i, true);
        }
        System.out.println(list);
        test(true, true, false, 10);
    }
}
