import org.apache.commons.math3.linear.MatrixUtils;
import org.apache.commons.math3.linear.RealMatrix;

import java.io.Serializable;
import java.util.Random;

public class Layer implements Serializable {
    private RealMatrix neurons;
    private RealMatrix weights;
    private RealMatrix error;
    private RealMatrix delta;
    private RealMatrix lastDelta; //delta z poprzedniej iteracji
    private int bias;

    //konstruktor dla warstwy pierwszej (z danymi wejściowymi)
    public Layer(int numberOfNeurons, int outputs, double[][] data, int bias) {
        this.bias = bias;
        if(bias == 0) {
            this.neurons = MatrixUtils.createRealMatrix(data);
        } else {
            //ustawienie wartości biasu na 1
            this.neurons = MatrixUtils.createRealMatrix(data.length,numberOfNeurons+bias);
            for(int i=0; i<neurons.getRowDimension(); i++) {
                for(int j=0; j<neurons.getColumnDimension(); j++) {
                    try {
                        neurons.setEntry(i, j, data[i][j]);
                    } catch (IndexOutOfBoundsException e) {
                        neurons.setEntry(i, j, 1);
                    }
                }
            }
        }

        this.weights = MatrixUtils.createRealMatrix(numberOfNeurons+bias, outputs+bias);
        setRandomValues();
    }

    //konstruktor dla wewnętrznych warstw
    public Layer(int numberOfNeurons, int outputs, int bias, int i, int numberOfLayers, int dataLength) {
        this.bias = bias;
        this.neurons = MatrixUtils.createRealMatrix(dataLength,numberOfNeurons+bias);
        //jeżeli jest to przedostatnia warstwa to przy ustalaniu wag nie bierzemy biasu pod uwagę (bo ostatnia warstwa nie ma biasu)
        if(i==numberOfLayers-2) {
            this.weights = MatrixUtils.createRealMatrix(numberOfNeurons+bias, outputs);
        } else {
            this.weights = MatrixUtils.createRealMatrix(numberOfNeurons+bias, outputs+bias);
        }
        setRandomValues();

        this.delta = MatrixUtils.createRealMatrix(dataLength,numberOfNeurons+bias);
        this.error = MatrixUtils.createRealMatrix(dataLength,numberOfNeurons+bias);
        this.lastDelta = MatrixUtils.createRealMatrix(dataLength,numberOfNeurons+bias);
    }

    //konstruktor dla ostatniej warstwy
    public Layer(int numberOfNeurons, int dataLength) {
        this.bias = 0;
        this.neurons = MatrixUtils.createRealMatrix(dataLength,numberOfNeurons);
        this.delta = MatrixUtils.createRealMatrix(dataLength,numberOfNeurons);
        this.error = MatrixUtils.createRealMatrix(dataLength,numberOfNeurons);
        this.lastDelta = MatrixUtils.createRealMatrix(dataLength,numberOfNeurons);
    }

    public void setRandomValues() {
        Random r = new Random();
        for(int i=0; i < weights.getRowDimension(); i++) {
            for(int j=0; j < weights.getColumnDimension(); j++) {
                weights.setEntry(i, j, r.nextDouble()*2.0-1.0);
            }
        }
    }

    public void setDelta() {
        for(int i=0; i<delta.getRowDimension(); i++) {
            for(int j=0; j<delta.getColumnDimension(); j++) {
                delta.setEntry(i, j, error.getEntry(i, j) * fd(neurons.getEntry(i, j)));
            }
        }

    }

    public double fd(double x) {
        return x * (1 - x);
    }

    public void activate() {
        double x;
        for(int i=0; i<neurons.getRowDimension(); i++) {
            for(int j=0; j<neurons.getColumnDimension(); j++) {
                x = 1 / (1 + Math.exp(- neurons.getEntry(i, j)));
                neurons.setEntry(i, j, x);
            }
        }

    }

    //aktualizowanie wag bez momentum
    public void updateWeights(RealMatrix delta, double eta) {

        weights = weights.add(((neurons.transpose().multiply(delta)).scalarMultiply(eta)));
    }

    //aktualizowanie wag z momentum
    public void updateWeights(RealMatrix delta, RealMatrix lastDelta, double eta, double momentum) {

        weights = weights.add(((neurons.transpose().multiply(delta)).scalarMultiply(eta))
                .add((neurons.transpose().multiply(lastDelta)).scalarMultiply(momentum)));
    }

    //wypisuje średni błąd
    public double aveError() {
        double tmp = 0;
        int row = error.getRowDimension(), column=error.getColumnDimension();
        for(int i=0; i<row; i++) {
            for(int j=0; j<column; j++) {
                tmp += Math.abs(error.getEntry(i, j));
            }
        }
        return tmp / (column * row);
    }

    public double getValue() {
        double sum = 0;
        for(int i=0; i<neurons.getRowDimension(); i++) {
            sum += neurons.getEntry(i, 0);
        }

        return sum/neurons.getRowDimension();
    }

    //wypisuje ładnie macierz
    public String print(RealMatrix m) {
        String tmp = "";
        for(int i=0; i<m.getRowDimension(); i++) {
            for(int j=0; j<m.getColumnDimension(); j++) {
                tmp += String.format("%.4f", m.getEntry(i, j)) + " ";
            }
            tmp += "\n";
        }
        return tmp;
    }

    public void setBias() {
        if(bias == 1) {
            for(int i=0; i<neurons.getRowDimension(); i++) {
                neurons.setEntry(i, neurons.getColumnDimension()-1, 1);
            }
        }
    }

    public RealMatrix getError() {
        return error;
    }

    public void setError(RealMatrix error) {
        this.error = error;
    }

    public RealMatrix getDelta() {
        return delta;
    }

    public RealMatrix getLastDelta() {
        return lastDelta;
    }

    public void setLastDelta(RealMatrix lastDelta) {
        this.lastDelta = lastDelta;
    }

    public RealMatrix getNeurons() {
        return neurons;
    }

    public void setNeurons(RealMatrix neurons) {
        this.neurons = neurons;
    }

    public RealMatrix getWeights() {
        return weights;
    }

    public void setWeights(RealMatrix weights) {
        this.weights = weights;
    }
}

