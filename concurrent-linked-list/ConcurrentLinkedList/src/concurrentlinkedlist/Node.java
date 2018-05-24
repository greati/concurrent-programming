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
public class Node {
    private Node next;
    private int data;
    
    public Node(int data) {
        this.data = data;
        this.next = null;
    }

    public Node(Node next) {
        this.data = 0;
        this.next = next;
    }

    public Node(Node next, int data) {
        this.next = next;
        this.data = data;
    }

    public Node getNext() {
        return next;
    }

    public void setNext(Node next) {
        this.next = next;
    }

    public int getData() {
        return data;
    }

    public void setData(int data) {
        this.data = data;
    }
}
