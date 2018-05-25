/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package concurrentlinkedlist;
import java.util.Random;
import java.util.logging.Level;
import java.util.logging.Logger;
import java.util.NoSuchElementException;
import java.util.concurrent.locks.ReentrantReadWriteLock;
import java.util.concurrent.locks.ReentrantLock;

/**
 *
 * @author carlosv
 */
public class ConcurrentLinkedList {
    private Node head;
    private Node tail;
    private int length;
    
    private final ReentrantReadWriteLock searchRemoveLock;
    private final ReentrantLock insertRemoveLock;
    
    private final boolean randomDelays;
    private Random randomGenerator;
    private static final int MAX_DELAY = 1000;
    
    public ConcurrentLinkedList() {
        this.head = null;
        this.tail = null;
        this.length = 0;
        this.randomDelays = false;
        
        boolean fair = true;
        this.searchRemoveLock = new ReentrantReadWriteLock(fair);
        this.insertRemoveLock = new ReentrantLock(fair);
    }
    
    public ConcurrentLinkedList(boolean randomDelays) {
        this.head = null;
        this.tail = null;
        this.length = 0;
        this.randomDelays = randomDelays;
        if (randomDelays) {
            this.randomGenerator = new Random();
        }
        
        boolean fair = true;
        this.searchRemoveLock = new ReentrantReadWriteLock(fair);
        this.insertRemoveLock = new ReentrantLock(fair);
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
    
    @Override
    public String toString() {
        this.searchRemoveLock.readLock().lock();
        try {
            String list = "[";
            Node n = this.head;
            while(n != null) {
                list += Integer.toString(n.getData());
                n = n.getNext();
                if (n != null)
                    list += ", ";
            }
            list += "]";

            return list;
        } finally {
            this.searchRemoveLock.readLock().unlock();
        }
    }
    
    // search and remove
    public void remove(Node n) {
        Node prev = this.getPrevious(n);
        this.remove(prev, n);
    }
    
    // search and remove
    public void removeAt(int pos) {
        if (pos > 0) {
            Node prev = this.getNodeAt(pos-1);
            this.remove(prev, prev.getNext());
        } else {
            this.remove(null, this.head);
        }
    }
    
    // search and remove
    public void removeValue(int data) {
        this.searchRemoveLock.readLock().lock();
        Node n, prev;
        try {
            n = this.search(data);
            if (n == null) {
                throw new NoSuchElementException();
            }
            prev = this.getPrevious(n);
        } finally {
            this.searchRemoveLock.readLock().unlock();
        }
        this.remove(prev, n);
    }
    
    // remove
    private void remove(Node prev, Node target) {
        this.searchRemoveLock.writeLock().lock();
        this.insertRemoveLock.lock();
        try {
            if (this.randomDelays) {
                Thread.sleep(this.randomGenerator.nextInt(MAX_DELAY));
            }
            if (target == this.head)
                this.head = target.getNext();
            else
                prev.setNext(target.getNext());
            if (target == this.tail)
                this.tail = prev;
            this.length--;
        } catch (InterruptedException ex){
            Logger.getLogger(ConcurrentLinkedList.class.getName()).
                    log(Level.SEVERE, null, ex);
        } finally {
            this.insertRemoveLock.unlock();
            this.searchRemoveLock.writeLock().unlock();
        }
    }
    
    // insert
    public void insert(int data) {
        Node n = new Node(data);
        this.insert(n);
    }
    
    // insert
    public void insert(Node n) {
        this.insertRemoveLock.lock();
        try {
            if (this.randomDelays) {
                Thread.sleep(this.randomGenerator.nextInt(MAX_DELAY));
            }
            if (this.length > 0)
                this.tail.setNext(n);
            else
                this.head = n;

            this.tail = n;
            this.length++;
        } catch(InterruptedException ex) {
            Logger.getLogger(ConcurrentLinkedList.class.getName()).
                    log(Level.SEVERE, null, ex);
        } finally {
            this.insertRemoveLock.unlock();  
        }
    }
    
    // search
    public Node search(int data) {
        this.searchRemoveLock.readLock().lock();
        try {
            Node i = this.head;
            while(i != null) {
                if (i.getData() == data)
                    return i;
                i = i.getNext();
            }
            throw new NoSuchElementException();
        } finally {
            this.searchRemoveLock.readLock().unlock();
        }
    }
    
    public int findPosition(int data) {
        this.searchRemoveLock.readLock().lock();
        try {
            if (this.randomDelays) {
                Thread.sleep(this.randomGenerator.nextInt(MAX_DELAY));
            }
            int pos = 0;
            Node i = this.head;
            while(i != null) {
                if (i.getData() == data)
                    return pos;
                i = i.getNext();
                pos++;
            }
            throw new NoSuchElementException();
        } catch (InterruptedException ex) {
            Logger.getLogger(ConcurrentLinkedList.class.getName()).
                    log(Level.SEVERE, null, ex);
            return -1;
        } finally {
            this.searchRemoveLock.readLock().unlock();
        }
    }
    
    // search
    public Node getPrevious(Node n) {
        this.searchRemoveLock.readLock().lock();
        try {
            Node prev = null;
            Node curr = this.head;
            while(curr != null) {
                if (curr == n) {
                    return prev;
                }

                prev = curr;
                curr = curr.getNext();
            }
            throw new NoSuchElementException();
        } finally {
            this.searchRemoveLock.readLock().unlock();
        }
    }
    
    // search
    public Node getNodeAt(int pos) {
        this.searchRemoveLock.readLock().lock();
        try {
            if (pos < 0 || pos >= this.length)
                throw new IllegalArgumentException();

            Node curr = this.head;
            for (int i = 0; i < pos; ++i) {
                curr = curr.getNext();
            }

            return curr;
        } finally {
            this.searchRemoveLock.readLock().unlock();
        }
    }
    
    // search
    public int getPosition(Node n) {
        this.searchRemoveLock.readLock().lock();
        try {
            int pos = 0;
            Node i = this.head;
            while(i != null) {
                if (i == n)
                    return pos;
                i = i.getNext();
                pos++;
            }
            throw new NoSuchElementException();
        } finally {
            this.searchRemoveLock.readLock().unlock();
        }
    }
}
