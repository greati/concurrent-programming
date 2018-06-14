/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package matrixmultiplication;

/**
 *
 * @author greati
 */
public abstract class Multiplier {
    
    public Matrix multiply(Matrix lhs, Matrix rhs) {
        if (lhs.getCols() == rhs.getRows())
            return _multiply(lhs,rhs);
        else
            return null;
    }
    
    public abstract Matrix _multiply(Matrix lhs, Matrix rhs);
    
}
