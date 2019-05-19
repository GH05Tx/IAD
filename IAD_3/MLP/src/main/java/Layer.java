import org.apache.commons.math3.linear.MatrixUtils;
import org.apache.commons.math3.linear.RealMatrix;

import java.io.Serializable;
import java.util.Random;

public class Layer implements Serializable {
    private RealMatrix neurons;
    private RealMatrix inputWeights;
    private RealMatrix error;
    private RealMatrix delta;
    private RealMatrix lastDelta; //delta z poprzedniej iteracji
    private int bias;

    //WARSTWA WEJŚCIA
    public Layer(int nrNeurons, int outputs, double[][] content, int bias) {
        this.bias = bias;
        if(bias == 0) {
            this.neurons = MatrixUtils.createRealMatrix(content);
        } else {
            //ustawienie wartości biasu na 1
            this.neurons = MatrixUtils.createRealMatrix(content.length,nrNeurons+bias);
            for(int i=0; i<neurons.getRowDimension(); i++) {
                for(int j=0; j<neurons.getColumnDimension(); j++) {
                    try {
                        neurons.setEntry(i, j, content[i][j]);
                    } catch (IndexOutOfBoundsException e) {
                        neurons.setEntry(i, j, 1);
                    }
                }
            }
        }
        this.inputWeights = MatrixUtils.createRealMatrix(nrNeurons+bias, outputs+bias);
        randomWeights();
    }

    //WARSTWY UKRYTE
    public Layer(int nrNeurons, int outputs, int bias, int i, int nrLayers, int dataLength) {
        this.bias = bias;
        this.neurons = MatrixUtils.createRealMatrix(dataLength,nrNeurons+bias);
        //jeżeli jest to przedostatnia warstwa to przy ustalaniu wag nie bierzemy biasu pod uwagę (bo ostatnia warstwa nie ma biasu)
        if(i==nrLayers-2) {
            this.inputWeights = MatrixUtils.createRealMatrix(nrNeurons+bias, outputs);
        } else {
            this.inputWeights = MatrixUtils.createRealMatrix(nrNeurons+bias, outputs+bias);
        }
        randomWeights();
        this.delta = MatrixUtils.createRealMatrix(dataLength,nrNeurons+bias);
        this.error = MatrixUtils.createRealMatrix(dataLength,nrNeurons+bias);
        this.lastDelta = MatrixUtils.createRealMatrix(dataLength,nrNeurons+bias);
    }

    //WARSTWA WYJŚCIA
    public Layer(int numberOfNeurons, int dataLength) {
        this.bias = 0;
        this.neurons = MatrixUtils.createRealMatrix(dataLength,numberOfNeurons);
        this.delta = MatrixUtils.createRealMatrix(dataLength,numberOfNeurons);
        this.error = MatrixUtils.createRealMatrix(dataLength,numberOfNeurons);
        this.lastDelta = MatrixUtils.createRealMatrix(dataLength,numberOfNeurons);
    }

    public void randomWeights() {
        Random rand = new Random();
        for(int i=0; i < inputWeights.getRowDimension(); i++) {
            for(int j=0; j < inputWeights.getColumnDimension(); j++) {
                inputWeights.setEntry(i, j, rand.nextDouble()*2.0-1.0);
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

    public void calcWeights(RealMatrix value, double factor) {
        //obliczenie wartości wag bez uwzględnienia współczynnika momentum
        inputWeights = inputWeights.add(((neurons.transpose().multiply(value)).scalarMultiply(factor)));
    }

    public void calcWeights(RealMatrix value, RealMatrix lastValue, double factor, double factorM) {
        //obliczenie wartości wag z uwzględnieniem współczynnika momentum
        inputWeights = inputWeights.add(((neurons.transpose().multiply(value)).scalarMultiply(factor))
                .add((neurons.transpose().multiply(lastValue)).scalarMultiply(factorM)));
    }

    public double aveError() {
        //zwraca błąd średni
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
        return inputWeights;
    }

    public void setWeights(RealMatrix weights) {
        this.inputWeights = weights;
    }
}

