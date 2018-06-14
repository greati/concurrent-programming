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
public class PooledMultiplier extends Multiplier {
    private ExecutorService pool;
    
    public PooledMultiplier(ExecutorService pool) {
        this.pool = pool;
    }
    
    @Override
    public Matrix _multiply(Matrix lhs, Matrix rhs) {
        
        Matrix c = new Matrix(lhs.getRows(), rhs.getCols(), 0);
        
        for (int i = 0; i < lhs.getRows(); ++i) {
            Runnable r = new MultiplicationTask(lhs, rhs, c, i);
            System.out.println("Line " + i);
            pool.execute(r);
        }
        
        pool.shutdown();    
        
        return c;
        
    }
        
}
