import org.apache.commons.math3.linear.MatrixUtils;
import org.apache.commons.math3.linear.RealMatrix;
import org.apache.commons.math3.linear.RealVector;

import java.io.*;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;

public class Net {
    private List<Layer> layers;
    private double eta;
    private double momentum;
    private double precision;
    private RealMatrix pattern;
    private int iter;

    public Net(double precision, int iter, int bias, double eta, double momentum, int[] tab, double[][] input, double[][] pattern) {
        this.precision = precision;
        this.iter = iter;
        this.eta = eta;
        this.momentum = momentum;
        layers = new ArrayList<Layer>();
        this.pattern = MatrixUtils.createRealMatrix(pattern);
        //dodajemy pierwszą warstwę neuronów (tą z danymi)
        layers.add(new Layer(tab[0], tab[1], input, bias));

        //dodajemy wewnętrzne warstwy
        for (int i = 1; i < tab.length - 1; i++) {
            layers.add(new Layer(tab[i], tab[i + 1], bias, i, tab.length, input.length));
        }

        //dodajemy ostatnią warstwę (tą bez wag)
        layers.add(new Layer(tab[tab.length - 1], input.length));

        //wypisuje ustawienia sieci
        System.out.println("Ustawienia sieci:");
        System.out.println("------------------------------");
        System.out.println("liczba warstw: " + layers.size());
        for (int i = 0; i < tab.length; i++) {
            System.out.println("liczba neuronów w warstwie " + (i + 1) + ": " + tab[i]);
        }
        if (bias == 0) {
            System.out.println("bias: NIE");
        } else {
            System.out.println("bias: TAK");
        }
        System.out.println("współczynnik nauki: " + eta);
        System.out.println("współczynnik momentum: " + momentum);
        System.out.println("------------------------------");
    }

    public void learn() {
        Date before = new Date();
        //index ostatniej warstwy
        int last = layers.size() - 1;
        //lista błędów do narysowania wykresu
        List<Double> errors = new ArrayList<Double>();
        List<Double> errors2 = new ArrayList<Double>();

        System.out.println("********** TRYB NAUKI **********");

        System.out.println("Bład wypisywany co 500 epok:");

        for (int i = 0; i < iter; i++) {
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
                layers.get(j + 1).useActivateFun();
                layers.get(j + 1).setBias();
            }

            //obliczamy błąd ostatniej warstwy (wzorzec - neurony warstwy ostatniej)
            layers.get(last).setError(pattern.subtract(layers.get(last).getNeurons()));

            //i zapisujemy go do listy błędów (żeby narysowć później wykres)
            errors.add(layers.get(last).getAvgError());

            if (layers.get(last).getAvgError() < precision) {
                System.out.println("Błąd mniejszy niż " + precision);
                System.out.println("Sieć nauczona po " + i + " iteracjach");
                System.out.println("Błąd: " + layers.get(last).getAvgError());
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
            if (momentum == 0 || i == 0) {
                for (int j = last - 1; j >= 0; j--) {
                    layers.get(j).updateWeights(layers.get(j + 1).getDelta(), eta);
                }
            } else {
                for (int j = last - 1; j >= 0; j--) {
                    layers.get(j).updateWeights(layers.get(j + 1).getDelta(), layers.get(j + 1).getLastDelta(), eta, momentum);
                }
            }

        }

        System.out.println("------------------------------");
        //wypisanie co obliczyła sieć a co powinno być
        System.out.println(printResult());
        //rysowanie wykresu
        Graph draw = new Graph();
        int run = 1;
        draw.drawPlot(errors, run);
        run++;
//        plotter.drawPlot(errors2,run);
//        zapis sieci do pliku
        saveNetworkToFile();

        //zapis błędów do pliku
        PrintWriter pw = null;
        try {
            pw = new PrintWriter("data/tryb_nauki_bledy.txt");
            for (Double err : errors) {
                pw.println(err);
            }
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } finally {
            pw.close();
        }

    }

    public double test() {
        String data = "";
        readNetworkFromFile();
        System.out.println("****** TRYB TESTOWANIA ******");
        for (int j = 0; j < layers.size() - 1; j++) {
            //neurony z warstwy j+1 = neurony z warstwy j * wagi tych neuronów
            layers.get(j + 1).setNeurons(layers.get(j).getNeurons().multiply(layers.get(j).getWeights()));
            //funkcja aktywacji
            layers.get(j + 1).useActivateFun();
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
        //zapis raportu do pliku
        PrintWriter out = null;
        try {
            out = new PrintWriter("data/tryb_testowy_raport.txt");
            out.println(data);
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } finally {
            out.close();
        }
        return layers.get(layers.size() - 1).getAvgError();
    }

    public void saveNetworkToFile() {
        ObjectOutputStream out = null;
        try {
            out = new ObjectOutputStream(new BufferedOutputStream(new FileOutputStream("data/network")));
            for (Layer item : layers) {
                out.writeObject(item);
            }
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            try {
                out.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    public void readNetworkFromFile() {
        ObjectInputStream in = null;
        //czyścimy zainicjalizowaną przez konstruktor listę
        layers.clear();

        //odczyt
        try {
            in = new ObjectInputStream(new BufferedInputStream(new FileInputStream("data/network")));
            while (true) {
                layers.add((Layer) in.readObject());
            }
        } catch (EOFException e) {
        } catch (IOException e) {
            e.printStackTrace();
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        } finally {
            try {
                in.close();
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
            if (Math.abs(myNumber - matrix.getEntry(i, 0)) < distance){
                index2 = 0;
                distance= Math.abs(myNumber - matrix.getEntry(i, 0));
            }
            if (Math.abs(myNumber - matrix.getEntry(i, 1)) < distance){
                index2 = 1;
                distance= Math.abs(myNumber - matrix.getEntry(i, 1));
            }
            if (Math.abs(myNumber - matrix.getEntry(i, 2)) < distance){
                index2 = 2;
                distance= Math.abs(myNumber - matrix.getEntry(i, 2));
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
