import org.apache.commons.math3.linear.MatrixUtils;
import org.apache.commons.math3.linear.RealMatrix;
import org.apache.commons.math3.linear.RealVector;

import java.io.*;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;

public class Net {
    private List<Layer> layers;
    private double factor;      //wspolczynnik nauki
    private double factorM;     //wspolczynnik momentum
    private double precision;
    private RealMatrix pattern;
    private int rounds;
    private int tmpArray[];
    private int tmpBias;

    public Net(double precision, int rounds, int bias, double eta, double momentum, int[] array, double[][] data, double[][] pattern) {
        this.precision = precision;
        this.rounds = rounds;
        this.factor = eta;
        this.factorM = momentum;
        this.tmpArray = array;
        this.tmpBias = bias;
        layers = new ArrayList<Layer>();
        this.pattern = MatrixUtils.createRealMatrix(pattern);
        //dodajemy pierwszą warstwę neuronów (tą z danymi)
        layers.add(new Layer(array[0], array[1], data, bias));
        //dodajemy wewnętrzne warstwy
        for (int i = 1; i < array.length - 1; i++) {
            layers.add(new Layer(array[i], array[i + 1], bias, i, array.length, data.length));
        }
        //dodajemy ostatnią warstwę (tą bez wag)
        layers.add(new Layer(array[array.length - 1], data.length));
    }

    public void learn() {
        //index ostatniej warstwy
        int last = layers.size() - 1;
        //lista błędów do narysowania wykresu
        List<Double> errors = new ArrayList<Double>();
        List<Double> errors2 = new ArrayList<Double>();

        System.out.println("********** TRYB NAUKI **********");

        System.out.println("Bład wypisywany co 500 epok:");

        for (int i = 0; i < rounds; i++) {
            //zapisanie delty z poprzedniej iteracji
            if (i > 0) {
                for (int j = 1; j < last; j++) {
                    layers.get(j).setLastDelta(layers.get(j).getDelta());
                }
            }

            for (int j = 0; j < layers.size() - 1; j++) {
                //neurony z warstwy j+1 = neurony z warstwy j * wagi tych neuronów
                layers.get(j + 1).setNeurons(layers.get(j).getNeurons().multiply(layers.get(j).getWeights()));
                //funkcja aktywacji
                layers.get(j + 1).activate();
                layers.get(j + 1).setBias();
            }

            //obliczamy błąd ostatniej warstwy (wzorzec - neurony warstwy ostatniej)
            layers.get(last).setError(pattern.subtract(layers.get(last).getNeurons()));

            //i zapisujemy go do listy błędów (żeby narysowć później wykres)
            errors.add(layers.get(last).aveError());

            if (layers.get(last).aveError() < precision) {
                System.out.println("Błąd mniejszy niż " + precision);
                System.out.println("Sieć nauczona po " + i + " iteracjach");
                System.out.println("Błąd: " + layers.get(last).aveError());
                break;
            }

            //wypisujemy średni błąd co 500 epok
//            if(i%100 == 0) {
            //System.out.println(layers.get(last).getAvgError());
//                saveNetworkToFile();
//                errors2.add(runTestMode());
//            }

            //obliczamy delte warstwy ostatniej
            //delta = błąd * pochodna z neuronów (mnożymy odpowiadające sobie elementy)
            layers.get(last).setDelta();

            //obliczanie błędów i delty warstw wewnętrznych
            for (int j = last - 1; j > 0; j--) {
                //błąd warstwy j = delta warstwy j+1 * macierz wag warstwy j transponowana
                layers.get(j).setError(layers.get(j + 1).getDelta().multiply(layers.get(j).getWeights().transpose()));
                //obliczamy delte warstwy j (analogicznie jak wyżej)
                layers.get(j).setDelta();
            }

            //aktualizowanie wag warstw wewnętrznych i wag warstwy pierwszej
            //wagi warstwy j += eta * (macierz neuronów warstwy j (transponowana) * delta warstwy j+1)
            //					+ momentum * (macierz neuronów warstwy j(transponowana) * delta warstwy j+1 z poprzedniej iteracji)
            if (factorM == 0 || i == 0) {
                for (int j = last - 1; j >= 0; j--) {
                    layers.get(j).updateWeights(layers.get(j + 1).getDelta(), factor);
                }
            } else {
                for (int j = last - 1; j >= 0; j--) {
                    layers.get(j).updateWeights(layers.get(j + 1).getDelta(), layers.get(j + 1).getLastDelta(), factor, factorM);
                }
            }

        }

        System.out.println("------------------------------");
        //wypisanie co obliczyła sieć a co powinno być
        System.out.println(printResult());

        //GENEROWANIE WYKRESU
        Graph draw = new Graph();
        int run = 1;
        draw.drawPlot(errors, run);
        run++;
        //ZAPIS SIECI DO PLIKU
        saveNet();

        //GENEROWANIE RAPORTU Z DANEGO PROCESU NAUKI
        PrintWriter saver = null;
        try {
            saver = new PrintWriter("results/RAPORT_NAUKA.txt");
            saver.println("\tRAPORT Z PROCESU NAUKI");
            saver.println();
            saver.println("CHARAKTERYSTYKA SIECI");
            saver.println("- Liczba warstw: " + tmpArray.length);
            for (int i = 0; i < layers.size(); i++) {
                saver.println("- Uklad neuronow na warstwach: " + tmpArray[i]);
            }
            if (tmpBias == 1) saver.println("- Bias wykorzystywany");
            else if (tmpBias == 0) saver.println("- Bias niewykorzystywany");
            saver.println("- Wartość wspołczynnika nauki: " + factor);
            saver.println("- Wartość wspołczynnika momentum: " + factorM);
            saver.println("- Liczba cykli: " + rounds);
            saver.println();
            saver.println("BŁĘDY OBLICZONE W KOLEJNYCH CYKLACH");
            for (Double err : errors) {
                saver.println(err);
            }
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } finally {
            saver.close();
        }

    }

    public double test() {
        String data = "";
        readNet();
        System.out.println("****** TRYB TESTOWANIA ******");
        for (int j = 0; j < layers.size() - 1; j++) {
            //neurony z warstwy j+1 = neurony z warstwy j * wagi tych neuronów
            layers.get(j + 1).setNeurons(layers.get(j).getNeurons().multiply(layers.get(j).getWeights()));
            //funkcja aktywacji
            layers.get(j + 1).activate();
            layers.get(j + 1).setBias();
        }

        data += printResult() + "-------------------------------\n";
//        data += "Błąd: " + layers.get(layers.size()-1).getAvgError() + "\n-------------------------------\n";
//        for(int i=layers.size()-1; i>=0; i--) {
//            data += "Warstwa " + (i+1) + ": \n";
//            data += "Wyjście:\n" + layers.get(i).print(layers.get(i).getNeurons());
//            if(i < layers.size()-1) {
//                data += "Wagi:\n" + layers.get(i).print(layers.get(i).getWeights());
//            }
//            data += "-------------------------------\n";
//        }

        System.out.println(data);
        PrintWriter saver = null;
        try {
            saver = new PrintWriter("results/RAPORT_TEST.txt");
            saver.println(data);
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } finally {
            saver.close();
        }
        return layers.get(layers.size() - 1).aveError();
    }

    public void saveNet() {
        ObjectOutputStream saver = null;
        try {
            saver = new ObjectOutputStream(new BufferedOutputStream(new FileOutputStream("results/net")));
            for (Layer item : layers) {
                saver.writeObject(item);
            }
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            try {
                saver.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    public void readNet() {
        ObjectInputStream reader = null;
        //czyścimy zainicjalizowaną przez konstruktor listę
        layers.clear();
        try {
            reader = new ObjectInputStream(new BufferedInputStream(new FileInputStream("results/net")));
            while (true) {
                layers.add((Layer) reader.readObject());
            }
        } catch (EOFException e) {
        } catch (IOException e) {
            e.printStackTrace();
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        } finally {
            try {
                reader.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    public int getIndex(RealVector row) {
        if (row.getEntry(0) == 1)
            return 0;
        else if (row.getEntry(1) == 1)
            return 1;
        else
            return 2;
    }

    public String printResult() {
        String data = "Wynik uzyskany przez sieć:\n";
        data += layers.get(layers.size() - 1).print(layers.get(layers.size() - 1).getNeurons());
        RealMatrix matrix = layers.get(layers.size() - 1).getNeurons();
        double myNumber = 1.0;
        List<Integer> result = new ArrayList<Integer>();
        for (int i = 0; i < matrix.getRowDimension(); i++) {
            int index2 = -1;
            double distance = 1;
            if (Math.abs(myNumber - matrix.getEntry(i, 0)) < distance) {
                index2 = 0;
                distance = Math.abs(myNumber - matrix.getEntry(i, 0));
            }
            if (Math.abs(myNumber - matrix.getEntry(i, 1)) < distance) {
                index2 = 1;
                distance = Math.abs(myNumber - matrix.getEntry(i, 1));
            }
            if (Math.abs(myNumber - matrix.getEntry(i, 2)) < distance) {
                index2 = 2;
                distance = Math.abs(myNumber - matrix.getEntry(i, 2));
            }

            result.add(index2);
        }
        //System.out.println(result);
        int FirstKindCount = 0, SecondKindCount = 0, ThridKindCount = 0;
        int success = 0;

        for (int i = 0; i < pattern.getRowDimension(); i++) {
            //System.out.println("Result: " + result.get(i)+ " Pattern: " + getIndex(pattern.getRowVector(i)));
            int index = getIndex(pattern.getRowVector(i));
            if (index == result.get(i)) {
                success++;
                if (index == 0) FirstKindCount++;
                if (index == 1) SecondKindCount++;
                if (index == 2) ThridKindCount++;
            }
        }
        System.out.println("Success rate of: ");
        System.out.println("All: " + (double) success / pattern.getRowDimension() * 100);
        System.out.println("First: " + (double) FirstKindCount / pattern.getRowDimension() * 3 * 100);
        System.out.println("Second: " + (double) SecondKindCount / pattern.getRowDimension() * 3 * 100);
        System.out.println("Third: " + (double) ThridKindCount / pattern.getRowDimension() * 3 * 100);

        data += "Wzorzec:\n";
        for (int i = 0; i < pattern.getRowDimension(); i++) {
            for (int j = 0; j < pattern.getColumnDimension(); j++) {
                //data += String.format("%.4f", pattern.getEntry(i, j)) + " ";
            }
            //data += "\n";
        }
        return data;
    }
}
