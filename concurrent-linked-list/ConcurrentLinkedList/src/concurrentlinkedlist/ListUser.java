/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package concurrentlinkedlist;

import java.util.NoSuchElementException;

/**
 *
 * @author carlosv
 */
public class ListUser extends Thread {
    
    public enum Operation {
        SEARCH,
        INSERTION,
        REMOVAL
    }
    
    private final Operation operation;
    private final Node node;
    private final ConcurrentLinkedList list;
    
    public ListUser(ConcurrentLinkedList list, Operation operation, Node n) {
        this.list = list;
        this.node = n;
        this.operation = operation;
    }
    
    /**
     * Run thread.
     * 
     */
    @Override
    public void run() {
        int value = this.node.getData();
        String v = "value " + Integer.toString(value);
        
        try {
            switch (this.operation) {
                case SEARCH:
                    System.out.println("searching for "+v);
                    int pos = this.list.findPosition(value);
                    System.out.println(v+" found at position "+
                            Integer.toString(pos));
                case INSERTION:
                    System.out.println("inserting "+v);
                    this.list.insert(value);
                    System.out.println(v+" inserted");
                case REMOVAL:
                    System.out.println("removing "+v);
                    this.list.removeValue(value);
                    System.out.println(v+" removed");
            }
        } catch (NoSuchElementException ex) {
            System.out.println(v+" not found");
        } finally {
            System.out.println(this.list);
        }
    }
}