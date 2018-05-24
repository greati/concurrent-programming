/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package concurrentlinkedlist;
import java.util.NoSuchElementException;
import java.lang.IllegalArgumentException;

/**
 *
 * @author carlosv
 */
public class ConcurrentLinkedList {
    private Node head;
    private Node tail;
    private int length;
    
    public ConcurrentLinkedList() {
        this.head = null;
        this.tail = null;
        this.length = 0;
    }

    public Node getHead() {
        return head;
    }

    public Node getTail() {
        return tail;
    }

    public int getLength() {
        return length;
    }
    
    // search and remove
    public void removeNode(Node n) {
        int pos = 0;
        Node prev = null;
        Node curr = this.head;
        while(curr != null) {
            if (curr == n) {
                this.remove(prev, curr);
                return;
            }
            
            prev = curr;
            curr = curr.getNext();
        }
        throw new NoSuchElementException();
    }
    
    // search and remove
    public void removeAt(int pos) {
        if (pos < 0 || pos >= this.length)
            throw new IllegalArgumentException();
        
        Node prev = null;
        Node curr = this.head;
        for (int i = 0; i < pos; ++i) {
            prev = curr;
            curr = curr.getNext();
        }
        
        this.remove(prev, curr);
    }
    
    // search and remove
    public void removeValue(int data) {
        int pos = 0;
        Node prev = null;
        Node curr = this.head;
        while(curr != null) {
            if (curr.getData() == data) {
                this.remove(prev, curr);
                return;
            }
            
            prev = curr;
            curr = curr.getNext();
        }
        throw new NoSuchElementException();
    }
    
    // remove
    private void remove(Node prev, Node target) {
        if (target == this.head)
            this.head = target.getNext();
        else
            prev.setNext(target.getNext());
        if (target == this.tail)
            this.tail = prev;
        this.length--;
    }
    
    // Insert
    public void insert(int data) {
        Node n = new Node(data);
        this.insert(n);
    }
    
    // Insert
    public void insert(Node n) {
        if (this.length > 0)
            this.tail.setNext(n);
        else
            this.head = n;
        
        this.tail = n;
        this.length++;
    }
    
    // search
    public Node search(int data) {
        int pos = 0;
        Node i = this.head;
        while(i != null) {
            if (i.getData() == data)
                return i;
            i = i.getNext();
            pos++;
        }
        return null;
    }
    
    // search
    public int getPosition(Node n) {
        int pos = 0;
        Node i = this.head;
        while(i != null) {
            if (i == n)
                return pos;
            i = i.getNext();
            pos++;
        }
        throw new NoSuchElementException();
    }
}
