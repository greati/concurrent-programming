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
public class MultiplicationTask implements Runnable {

    private Matrix lhs, rhs, res = null;
    private int line;
    
    public MultiplicationTask(Matrix lhs, Matrix rhs, Matrix res, int line) {
        this.lhs = lhs;
        this.rhs = rhs;
        this.res = res;
        this.line = line;
    }
    
    @Override
    public void run() {
        double l[] = lhs.computeMultLine(rhs, line);
        res.getData()[line] = l;
    }
    
}
