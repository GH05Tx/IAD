import org.apache.commons.math3.linear.MatrixUtils;
import org.apache.commons.math3.linear.RealMatrix;
import org.apache.commons.math3.linear.RealVector;
import java.io.*;
import java.util.ArrayList;
import java.util.List;

public class Net {

    private int rounds;
    private int tmpArray[];
    private int tmpBias;
    private double factor;      //wspolczynnik nauki
    private double factorM;     //wspolczynnik momentum
    private double precision;
    private RealMatrix pattern;
    private List<Layer> layers;
    private int stop;
    private int safeStop;       //bezpieczny warunek stopu - w przypadku nie spełnienia określonej precyzji

    public Net(double prec, int rounds, int bias, double factor, double factorM, int[] array, double[][] data, double[][] pattern, int stop) {
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
        this.precision = prec;
        this.rounds = rounds;
        this.factor = factor;
        this.factorM = factorM;
        this.tmpArray = array;
        this.tmpBias = bias;
        this.safeStop = 50000;
        this.stop=stop;
    }

    public void learn() {
        //index ostatniej warstwy
        int last = layers.size() - 1;
        List<Double> calc = new ArrayList<Double>();
        List<Double> file = new ArrayList<Double>();

        System.out.println("\tNAUKA SIECI");

        System.out.println("Bład wypisywany co 500 epok:");

        int iterMax, i=0;
        if(stop==0) { iterMax=safeStop; }
        else { iterMax=rounds; }

        do {
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

            //obliczenie błędu w każdej epoce
            //następnie dodanie go do listy na potrzeby późniejszych działań
            layers.get(last).setError(pattern.subtract(layers.get(last).getNeurons()));
            calc.add(layers.get(last).aveError());

            if(i%100==0) { file.add(layers.get(last).aveError());}

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
                    layers.get(j).calcWeights(layers.get(j + 1).getDelta(), factor);
                }
            } else {
                for (int j = last - 1; j >= 0; j--) {
                    layers.get(j).calcWeights(layers.get(j + 1).getDelta(), layers.get(j + 1).getLastDelta(), factor, factorM);
                }
            }
        i++;
        } while (i<iterMax || layers.get(last).aveError() < precision);

        System.out.println("------------------------------");
        //wypisanie co obliczyła sieć a co powinno być
        System.out.println(calcStat());

        //GENEROWANIE WYKRESU
        Graph draw = new Graph();
        draw.drawPlot(calc);

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
            for (int j = 0; i < layers.size(); i++) {
                saver.println("- Uklad neuronow na warstwach: " + tmpArray[j]);
            }
            if (tmpBias == 1) saver.println("- Bias wykorzystywany");
            else if (tmpBias == 0) saver.println("- Bias niewykorzystywany");
            saver.println("- Wartość wspołczynnika nauki: " + factor);
            saver.println("- Wartość wspołczynnika momentum: " + factorM);
            saver.println("- Liczba epok: " + rounds);
            saver.println();
            saver.println("BŁĘDY OBLICZONE CO 100 EPOK");
            for (Double err : file) {
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
        System.out.println("\tTESTOWANIE SIECI");
        for (int j = 0; j < layers.size() - 1; j++) {
            //neurony z warstwy j+1 = neurony z warstwy j * wagi tych neuronów
            layers.get(j + 1).setNeurons(layers.get(j).getNeurons().multiply(layers.get(j).getWeights()));
            //funkcja aktywacji
            layers.get(j + 1).activate();
            layers.get(j + 1).setBias();
        }

        data += calcStat() + "-------------------------------\n";
        System.out.println(data);
        PrintWriter saver = null;
        try {
            saver = new PrintWriter("results/RAPORT_TEST.txt");
            saver.println("\tRAPORT Z PROCESU TESTOWANIA");
            saver.println(data);
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } finally {
            saver.close();
        }
        return layers.get(layers.size() - 1).aveError();
    }

    //ZAPIS SIECI DO PLIKU
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

    //ODCZYT SIECI Z PLIKU
    public void readNet() {
        ObjectInputStream reader = null;
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

    public String calcStat() {
        String data = layers.get(layers.size() - 1).print(layers.get(layers.size() - 1).getNeurons());
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

        int counter1 = 0, counter2 = 0, counter3 = 0;
        int success = 0;

        for (int i = 0; i < pattern.getRowDimension(); i++) {
            int compare = getIndex(pattern.getRowVector(i));
            if (compare == result.get(i)) {
                success++;
                if (compare == 0) { counter1++; }
                else if (compare == 1) { counter2++; }
                else if (compare == 2) { counter3++; }
            }
        }

        System.out.println("Success rate of: ");
        System.out.println("All: " + (double) success / pattern.getRowDimension() * 100);
        System.out.println("First: " + (double) counter1 / pattern.getRowDimension() * 3 * 100);
        System.out.println("Second: " + (double) counter2 / pattern.getRowDimension() * 3 * 100);
        System.out.println("Third: " + (double) counter3 / pattern.getRowDimension() * 3 * 100);

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
