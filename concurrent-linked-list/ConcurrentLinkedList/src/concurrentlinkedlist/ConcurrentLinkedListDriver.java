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
public class ConcurrentLinkedListDriver {
    
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        ConcurrentLinkedList l1 = new ConcurrentLinkedList();
        Node n = new Node(33);
        l1.insert(10);
        l1.insert(5);
        l1.insert(n);
        l1.insert(7);
        System.out.println(l1.getPosition(n));
        System.out.println(l1.getPosition(l1.search(5)));
        System.out.println(l1);
        l1.remove(n);
        System.out.println(l1);
        l1.removeAt(1);
        System.out.println(l1);
        System.out.println(l1.getLength());
        l1.insert(-99);
        System.out.println(l1);
        l1.remove(l1.getHead());
        System.out.println(l1);
        l1.remove(l1.getTail());
        System.out.println(l1);
    }
}
