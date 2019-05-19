import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        /*
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
        */

        double prec=0.18, factor=0.01, factorM=0;
        int round=9000, choiceBias=1;
        int[] array = {4,2,3};

        DataReader dataLearn = new DataReader("data/irys_learn.txt");
        Net network1 = new Net(prec, round, choiceBias, factor, factorM, array, dataLearn.getInput(), dataLearn.getPattern());
        network1.learn();


/*
        DataReader dataTest = new DataReader("data/irys_test.txt");
        Net network2 = new Net(prec, round, choiceBias, factor, factorM, array, dataTest.getInput(), dataTest.getPattern());
        network2.test();

 */
        /*
        switch (choiceWork) {
            case "n":
            case "N": {
                data = new DataReader("data/irys_learn.txt");
                //data = new DataReader("data/seeds_learn.csv");
                Net network = new Net(prec, round, choiceBias, factor, factorM, array, data.getInput(), data.getPattern());
                network.learn();
            }
            break;

            case "t":
            case "T": {
                data = new DataReader("data/irys_test.txt");
                //data = new DataReader("data/seeds_test.csv");
                Net network = new Net(prec, round, choiceBias, factor, factorM, array, data.getInput(), data.getPattern());
                network.test();
            }
            break;
        }*/
    }
}
