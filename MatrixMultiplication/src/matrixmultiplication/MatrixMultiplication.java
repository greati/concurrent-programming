/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package matrixmultiplication;

import java.util.concurrent.Executors;

/**
 *
 * @author greati
 */
public class MatrixMultiplication {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
        
        Matrix m1 = new Matrix(10,4,3, new PooledMultiplier(Executors.newCachedThreadPool()));
        Matrix m2 = new Matrix(4,4,10);
                
        System.out.println(m1.multiply(m2));
        
    }
    
}
