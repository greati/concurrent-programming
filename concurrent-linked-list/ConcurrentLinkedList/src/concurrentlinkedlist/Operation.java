/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package concurrentlinkedlist;

import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author vitorgreati
 */
public class Operation extends Thread {
    
    private final int orderNumber;
    private final OpType type;
    private final ConcurrentLinkedList ll;
        
    enum OpType {
        INSERT,
        REMOVE,
        SEARCH
    }
    
    public Operation(int orderNumber, OpType type, ConcurrentLinkedList ll) {
        this.orderNumber = orderNumber;
        this.type = type;
        this.ll = ll;
    }
    
    @Override
    public void run() {
    
        switch (this.type) {
            case INSERT:
                ll.insert(orderNumber, this.orderNumber);
                break;
            case REMOVE:
                try {
                    int p = 0;
                    ll.removeNode(orderNumber, new Node(p));
                } catch (Exception e) {}
                break;
            case SEARCH:
                int p = 0;
                ll.search(orderNumber, p);
                break;
                
        }
        
    }
    
}
