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
public class Matrix {
    
    private Multiplier multiplier = null;
    private double[][] data = null;
    private int rows;
    private int cols;
        
    public Matrix(int rows, int cols, double def, Multiplier multiplier) {
        this.rows = rows;
        this.cols = cols;
        data = new double[rows][cols];
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                data[i][j] = def;
        this.multiplier = multiplier;
    }
    
    public Matrix(int rows, int cols, double def) {
        this.rows = rows;
        this.cols = cols;
        data = new double[rows][cols];
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                data[i][j] = def;
        this.multiplier = new SequentialMultiplier();    
    }
    
    public double[] computeMultLine(Matrix rhs, int i) {        
        if (this.getCols() == rhs.getRows()) {
            double line[] = new double[this.getCols()];
            for (int j = 0; j < this.getCols(); ++j)
                for (int k = 0; k < this.getCols(); ++k)
                    line[j] += getData()[i][k] * rhs.getData()[k][j];
            return line;
        } else return null;
    }
    
    public Matrix multiply(Matrix rhs) {
        return multiplier.multiply(this, rhs);
    }

    /**
     * @return the rows
     */
    public int getRows() {
        return rows;
    }

    /**
     * @param rows the rows to set
     */
    public void setRows(int rows) {
        this.rows = rows;
    }

    /**
     * @return the cols
     */
    public int getCols() {
        return cols;
    }

    /**
     * @param cols the cols to set
     */
    public void setCols(int cols) {
        this.cols = cols;
    }
    
    public String toString() {
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < this.rows; ++i) {
            
            for (int j = 0; j < this.cols; ++j)
                sb.append(this.getData()[i][j] + " ");
          
            sb.append("\n");
        }
        return sb.toString();
    }

    /**
     * @return the data
     */
    public double[][] getData() {
        return data;
    }

    /**
     * @param data the data to set
     */
    public void setData(double[][] data) {
        this.data = data;
    }
    
}
