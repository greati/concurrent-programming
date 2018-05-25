/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package concurrentlinkedlist;


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
    private final int value;
    private final ConcurrentLinkedList list;
    
    public ListUser(ConcurrentLinkedList list, Operation operation, int value) {
        this.list = list;
        this.value = value;
        this.operation = operation;
    }
    
    /**
     * Run thread.
     * 
     */
    @Override
    public void run() {
        switch (this.operation) {
            case SEARCH:
                this.list.findPosition(value);
                break;
            case INSERTION:
                this.list.insert(value);
                break;
            case REMOVAL:
                this.list.removeValue(value);
                break;
        }

    }
}