/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package concurrentlinkedlist;
import java.util.NoSuchElementException;
import java.lang.IllegalArgumentException;
import java.util.concurrent.Semaphore;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;
import java.util.logging.Level;
import java.util.logging.Logger;
import jdk.nashorn.internal.codegen.types.NumericType;
import sun.nio.ch.NativeThread;

/**
 *
 * @author carlosv
 */
public class ConcurrentLinkedList {
    private Node head;
    private Node tail;
    private int length;
    
    private final Semaphore semQueue;
    private final Semaphore semRemove;
    private final Semaphore noOperations;
    private final Semaphore noInsert;
    
    private final Lock lock = new ReentrantLock(true);
    
    final Condition queue = lock.newCondition();
    
    final Condition hasOperations = lock.newCondition();
    
    final Condition removeIn = lock.newCondition();
    
    final Condition insertIn = lock.newCondition();
    
    private volatile int currentHead = 0;
    
    private volatile boolean removing;
    private volatile boolean inserting;
    private volatile int numberOperations;
    
    public ConcurrentLinkedList() {
        this.head = null;
        this.tail = null;
        this.length = 0;
        this.semQueue = new Semaphore(1, true);
        this.semRemove = new Semaphore(1, true);
        this.noOperations = new Semaphore(1, true);
        this.noInsert = new Semaphore(1, true);
        this.removing = false;
        this.inserting = false;
        this.numberOperations = 0;
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
    public void removeNode(long i, Node n) {
        lock.lock();
        try {
            
            System.out.println("x Remove node entered.");
            
            if (currentHead != i) {
                System.out.println(".. Remove node enqueued.");
                queue.await();
            }
            
            
            if (numberOperations > 0) {
                System.out.println("... Remove node waiting operations to finish.");
                hasOperations.await();
            }

            System.out.println("..x Removing node.");
            
            currentHead++;

            queue.signal();
            
            removing = true;
            
            numberOperations++;
            
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
            
            numberOperations--;
            
            removing = false;
            
            hasOperations.signal();
                                    
            System.out.println("X Removed.");
            
            throw new NoSuchElementException();
        } catch (InterruptedException ex) {
            Logger.getLogger(ConcurrentLinkedList.class.getName()).log(Level.SEVERE, null, ex);
        }finally {
            lock.unlock();
        }
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
    public void insert(long i, int data) {
        try {
            lock.lock();
            
            System.out.println("* Insert node.");

            if (currentHead != i) {
                System.out.println(".. Insert node enqueued.");
                queue.await();
            }
            
            currentHead++;
            
            if (inserting) {
                System.out.println("... Waiting insert operation to finish.");
                insertIn.await();
            }
            
            if (removing) {
                System.out.println(".... Waiting remove operation to finish.");
                removeIn.await();
            }
            
            System.out.println("..* Inserting node.");

            queue.signal();
            
            inserting = true;
            
            numberOperations++;
            
            Node n = new Node(data);
            this.insert(n);
            
            numberOperations--;
            
            inserting = false;
            
            insertIn.signal();
                        
            System.out.println("** Inserted.");            
            
            if (numberOperations == 0)
                hasOperations.signal();
            
        } catch (InterruptedException ex) {
            Logger.getLogger(ConcurrentLinkedList.class.getName()).log(Level.SEVERE, null, ex);
        } finally {
            lock.unlock();
        }
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
    public Node search(long ii, int data) {
        try {
            lock.lock(); 
            System.out.println("o Search node.");
            if (currentHead != ii) {
                System.out.println(".. Search node enqueued.");
                queue.await();
            }
            
            currentHead++;           
            
            if (removing) {
                System.out.println(".. Search node waiting removal to finish.");
                removeIn.await();
            }
            
            System.out.println("..o Searching node.");
            
            queue.signal();
            
            numberOperations++;

            int pos = 0;
            Node i = this.head;
            while(i != null) {
                if (i.getData() == data) {
                    return i;
                }
                i = i.getNext();
                pos++;
            }
            Thread.sleep(1000);
            
            numberOperations--;
                        
            if (numberOperations == 0)
                hasOperations.signal();
                        
            System.out.println("oo Search finish.");
            
        } catch (InterruptedException ex) {
            Logger.getLogger(ConcurrentLinkedList.class.getName()).log(Level.SEVERE, null, ex);
        } finally {
            lock.unlock();
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
