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
public class SequentialMultiplier extends Multiplier {

    @Override
    public Matrix _multiply(Matrix lhs, Matrix rhs) {
        
        Matrix c = new Matrix(lhs.getRows(), rhs.getCols(), 0);
        
        for (int i = 0; i < lhs.getRows(); ++i) {
            double l[] = lhs.computeMultLine(rhs, i);
            c.getData()[i] = l;
        }    
        
        return c;
    }
    
}
