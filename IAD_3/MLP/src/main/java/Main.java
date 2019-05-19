import java.util.Scanner;

public class Main {
    public static void main(String[] args) {

        double prec, factor, factorM;
        int round, choiceBias, stop, ster;
        int[] array;
        Scanner scan = new Scanner(System.in);

        // STOP - WARUNEK ZATRZYMANIA PROGRAMU
        // 0 - wykonanie określonej liczby iteracji
        // 1 - spełnienie określonej precyzji
        // w przypadku 1 - jeśli program nie spełni określonej precyzji
        // zatrzyma się na bezpiecznym warunku stopu czyli 50 000 iteracji

        System.out.println("Wprowadź dane z konsoli bądź wybierz 1 ze scenariuszy testowych:");
        System.out.println("- wprowadz dane   [1]");
        System.out.println("- scenariusz no.1 [2]");
        System.out.println("- scenariusz no.2 [3]");
        System.out.println("- scenariusz no.3 [4]");
        System.out.println("- scenariusz no.4 [5]");
        ster = scan.nextInt();
        if (ster == 1) {
            System.out.println("KONFIGURACJA SIECI");
            //System.out.println("Okresl tryb pracy - nauka/testowanie: [n/t] ");
            //String choiceWork = scan.nextLine();
            System.out.println("Podaj liczbe warstw sieci: ");
            int layers = scan.nextInt();
            array = new int[layers];
            int nr = 1;
            for (int i = 0; i < layers; i++) {
                System.out.println("Podaj liczbe neuronow w " + nr + " warstwie:");
                array[i] = scan.nextInt();
                nr++;
            }
            System.out.println("Czy bias ma byc brany pod uwage? [0/1] ");
            choiceBias = scan.nextInt();
            System.out.println("Okresl wspolczynnik nauki: ");
            factor = scan.nextDouble();
            System.out.println("Okresl wspolczynnik momentum: ");
            factorM = scan.nextDouble();
            System.out.println("Okresl warunek stopu: [0 - epoki | 1 - precyzja]");
            stop = scan.nextInt();
            System.out.println("Okresl precyzje: ");
            prec = scan.nextDouble();
            System.out.println("Okresl liczbe epok: ");
            round = scan.nextInt();

        } else if (ster == 2) {
            prec = 0.18;
            factor = 0.01;
            factorM = 0;
            round = 9000;
            choiceBias = 1;
            stop = 1;
            array = new int[] {4, 2, 3};
        } /*
        else if (ster == 3) {
        } else if (ster == 4) {
        } else if (ster == 5) {
        }*/
        else {
            prec = 0.18;
            factor = 0.01;
            factorM = 0;
            round = 9000;
            choiceBias = 1;
            stop = 1;
            array = new int[] {4, 2, 3};
        }


        DataReader dataLearn = new DataReader("data/irys_learn.txt");
        Net network1 = new Net(prec, round, choiceBias, factor, factorM, array, dataLearn.getInput(), dataLearn.getPattern(), stop);
        network1.learn();

        DataReader dataTest = new DataReader("data/irys_test.txt");
        Net network2 = new Net(prec, round, choiceBias, factor, factorM, array, dataTest.getInput(), dataTest.getPattern(), stop);
        network2.test();


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
