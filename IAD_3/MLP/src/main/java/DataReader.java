import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class DataReader {

    private double[][] input;
    private double[][] pattern;
    private String[][] data;

    public DataReader(String path) {
        String line = "";
        String cvsSplitBy = ",";
        List<String[]> list = new ArrayList<String[]>();

        try (BufferedReader br = new BufferedReader(new FileReader(path))) {
            while ((line = br.readLine()) != null) {
                list.add(line.split(cvsSplitBy));
            }

        } catch (IOException e) {
            e.printStackTrace();
        }

        data = new String[list.size()][];
        data = list.toArray(data);

        input = new double[data.length][data[0].length - 1]; //odejmuje 1 bo w ostatniej kolumnie są nazwy

        for(int i=0; i<data.length; i++) {
            for(int j=0; j<data[0].length - 1; j++) {
                input[i][j] = Double.parseDouble(data[i][j]);
            }
        }
        pattern = new double[data.length][3];

        for(int i=0; i<data.length; i++) {
            for(int j=data[0].length-1; j<data[0].length; j++) {
                if(data[i][j].equals("Iris-setosa") || data[i][j].equals("1")) {
                    pattern[i][0] = 1;
                    pattern[i][1] = 0;
                    pattern[i][2] = 0;
                } else if (data[i][j].equals("Iris-versicolor") || data[i][j].equals("2")) {
                    pattern[i][0] = 0;
                    pattern[i][1] = 1;
                    pattern[i][2] = 0;
                } else {
                    pattern[i][0] = 0;
                    pattern[i][1] = 0;
                    pattern[i][2] = 1;
                }
            }
        }
    }
/*
    public DataReader(String path) {
        init(path);
    }

    public void init(String path) {

        String line = "";
        String cvsSplitBy = ",";
        List<String[]> list = new ArrayList<String[]>();

        try (BufferedReader br = new BufferedReader(new FileReader(path))) {
            while ((line = br.readLine()) != null) {
                list.add(line.split(cvsSplitBy));
            }

        } catch (IOException e) {
            e.printStackTrace();
        }

        data = new String[list.size()][];
        data = list.toArray(data);

        input = new double[data.length][data[0].length - 1]; //odejmuje 1 bo w ostatniej kolumnie są nazwy

        for(int i=0; i<data.length; i++) {
            for(int j=0; j<data[0].length - 1; j++) {
                input[i][j] = Double.parseDouble(data[i][j]);
            }
        }
        pattern = new double[data.length][3];

        for(int i=0; i<data.length; i++) {
            for(int j=data[0].length-1; j<data[0].length; j++) {
                if(data[i][j].equals("Iris-setosa") || data[i][j].equals("1")) {
                    pattern[i][0] = 1;
                    pattern[i][1] = 0;
                    pattern[i][2] = 0;
                } else if (data[i][j].equals("Iris-versicolor") || data[i][j].equals("2")) {
                    pattern[i][0] = 0;
                    pattern[i][1] = 1;
                    pattern[i][2] = 0;
                } else {
                    pattern[i][0] = 0;
                    pattern[i][1] = 0;
                    pattern[i][2] = 1;
                }
            }
        }
    }
*/
    public double[][] getInput() {
        return input;
    }

    public double[][] getPattern() {
        return pattern;
    }

}
