import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        System.out.println("KONFIGURACJA SIECI");
        //System.out.println("Okresl tryb pracy - nauka/testowanie: [n/t] ");
        //String choiceWork = scan.nextLine();
        System.out.println("Podaj liczbe warstw sieci: ");
        int layers = scan.nextInt();
        int[] array = new int[layers];
        int nr = 1;
        for (int i = 0; i < layers; i++) {
            System.out.println("Podaj liczbe neuronow w " + nr + " warstwie:");
            array[i] = scan.nextInt();
            nr++;
        }
        System.out.println("Czy bias ma byc brany pod uwage? [0/1] ");
        int choiceBias = scan.nextInt();
        System.out.println("Okresl wspolczynnik nauki: ");
        double factor = scan.nextDouble();
        System.out.println("Okresl wspolczynnik momentum: ");
        double factorM = scan.nextDouble();
        System.out.println("Okresl precyzje: ");
        double prec = scan.nextDouble();
        System.out.println("Okresl liczbe cykli: ");
        int round = scan.nextInt();

        DataReader data = new DataReader("data/iris_learn.csv");
        Net network = new Net(prec, round, choiceBias, factor, factorM, array, data.getInput(), data.getPattern());
        network.learn();
        System.out.println();
        network.test();
        /*
        switch (choiceWork) {
            case "n":
            case "N": {
                data = new DataReader("data/iris_learn.csv");
                //data = new DataReader("data/seeds_learn.csv");
                Net network = new Net(prec, round, choiceBias, factor, factorM, array, data.getInput(), data.getPattern());
                network.learn();
            }
            break;

            case "t":
            case "T": {
                data = new DataReader("data/iris_test.csv");
                //data = new DataReader("data/seeds_test.csv");
                Net network = new Net(prec, round, choiceBias, factor, factorM, array, data.getInput(), data.getPattern());
                network.test();
            }
            break;
        }*/
    }
}
