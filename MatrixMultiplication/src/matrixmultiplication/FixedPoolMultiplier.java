/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package matrixmultiplication;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

/**
 *
 * @author greati
 */
public class FixedPoolMultiplier extends Multiplier {

    private int numThreads;
    private ExecutorService pool;
    
    public FixedPoolMultiplier(int numThreads) {
        this.numThreads = numThreads;
    }
    
    @Override
    public Matrix _multiply(Matrix lhs, Matrix rhs) {

        pool = Executors.newFixedThreadPool(this.numThreads);
        
        Matrix c = new Matrix(lhs.getRows(), rhs.getCols(), 0);
        
        for (int i = 0; i < lhs.getRows(); ++i) {
            Runnable r = new MultiplicationTask(lhs, rhs, c, i);
            System.out.println("FPM: Line " + i);
            pool.execute(r);
        }
        
        pool.shutdown();    
        
        return c;
        
    }
    
}
