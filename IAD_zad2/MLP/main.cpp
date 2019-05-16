#include "include/Layer.h"
#include "include/Perceptron.h"
#include "include/Space.h"
#include "include/Gnuplot.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <ctime>
#include <unistd.h>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace chrono;

void printSpace(const Space& space){
    for(int i = 0; i < space.size(); i++){
        for(int d = 0; d < space.dimension(); d++){
            cout << space[i][d] << " ";
        }
        cout << endl;
    }
}

void printUsage(const string& info){
    cout << info << endl << endl;
    cout << "usage: ./perceptron\n"
            "\t\t-N x,y,z...            liczba neuronów w kolejnych warstwach, pierwsza warstwa jest nieprzetwarzająca\n"
            "\t\t-B 0,1...              bias w warstwach przetwarzających, 0 - nie ma, 1 - jest\n"
            "\t\t-i filename,filename   pliki z danymi wejściowymi, zbiór uczący i testowy\n"
            "\t\t-e filename,filename   pliki z oczekiwanymi danymi wyjściowymi, zbiór uczący i testowy\n"
            "\t\t-I int                 liczba iteracji\n"
            "\t\t-S double              współczynnik szybkości nauki\n"
            "\t\t[-M double             opcjonalne, współczynnik momentum\n"
            "\t\t[-R                    opcjonalne, mieszanie kolejności danych wejściowych\n\n";
    exit(0);
}

void printMatrix(vector<vector<int>> matrix){
    for(unsigned int i = 0; i < matrix.size(); i++){
        for(unsigned int j = 0; j < matrix[i].size(); j++){
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }
}

int checkClass(const double* outputs, int noOfOutputs){
    int maxIndex = 0;
    for(int i = 0; i < noOfOutputs; i++){
        if(outputs[i] > outputs[maxIndex])
            maxIndex = i;
    }
    return maxIndex;
}

double accuracyTest(Perceptron* per, const Space& inputsData, const Space& outputsData){
    int counter = 0;
    for(int i = 0; i < inputsData.size(); i++){
        const double* outputs = per->test(inputsData[i], outputsData[i]);
        int foundClass = checkClass(outputs, per->getNoOfOutputs());
        int realClass = checkClass(outputsData[i], per->getNoOfOutputs());
        if(foundClass == realClass)
            counter++;
    }
    return ((double)counter) / inputsData.size();
}

int main(int argc, char** argv){
    srand(time(NULL));
    Gnuplot gnuplot;
    cout << std::fixed << std::setprecision(3);

    //parametry obowiązkowe
    vector<int> layersDescription;
    vector<bool> biasFlags;
    ifstream fileInputsLearn;
    ifstream fileInputsTest;
    ifstream fileOutputsLearn;
    ifstream fileOutputsTest;
    int noOfIterations = 0;
    double learningSpeed = 0;

    //parametry opcjonalne
    double momentum = 0;
    bool randomFlag = false;

    //potrzebne do sprawdzania subopcji
    char* subopts;
    char* value;
    char* tokens[] = {
            NULL
    };

    //sprawdzenie opcji
    int opt;
    while((opt = getopt(argc, argv, "N:B:i:e:I:RS:M:")) != -1){
        switch(opt){
            case 'N':
                subopts = optarg;
                while(*subopts != '\0'){
                    getsubopt(&subopts, tokens, &value);
                    layersDescription.push_back(atoi(value));
                }
                break;
            case 'B':
                subopts = optarg;
                while(*subopts != '\0'){
                    getsubopt(&subopts, tokens, &value);
                    biasFlags.push_back(atoi(value));
                }
                break;
            case 'i':
                subopts = optarg;
                getsubopt(&subopts, tokens, &value);    //zbiór uczący
                fileInputsLearn.open(value);
                getsubopt(&subopts, tokens, &value);   //zbiór testowy
                fileInputsTest.open(value);
                break;
            case 'e':
                subopts = optarg;
                getsubopt(&subopts, tokens, &value);    //zbiór uczący
                fileOutputsLearn.open(value);
                getsubopt(&subopts, tokens, &value);   //zbiór testowy
                fileOutputsTest.open(value);
                break;
            case 'I':
                noOfIterations = atoi(optarg);
                break;
            case 'R':
                randomFlag = true;
                break;
            case 'S':
                learningSpeed = atof(optarg);
                break;
            case 'M':
                momentum = atof(optarg);
                break;
        }
    }

    //stworzenie perceptronu
    Perceptron* per = new Perceptron(layersDescription, biasFlags);
    per->setLearningSpeed(learningSpeed);
    per->setMomentum(momentum);

    //wczytywanie danych
    Space inputsLearnData(per->getNoOfInputs(), fileInputsLearn, per->getNoOfInputs());
    Space inputsTestData(per->getNoOfInputs(), fileInputsTest, per->getNoOfInputs());
    Space outputsLearnData(per->getNoOfOutputs(), fileOutputsLearn, per->getNoOfOutputs());
    Space outputsTestData(per->getNoOfOutputs(), fileOutputsTest, per->getNoOfOutputs());

    //zamkniecie plikow
    fileInputsLearn.close();
    fileInputsTest.close();
    fileOutputsLearn.close();
    fileOutputsTest.close();


    //nauka perceptronu---------------------------------------

    //kolejność wzorców wejściowych
    int* indexs = new int[inputsLearnData.size()];
    for(int i = 0; i < inputsLearnData.size(); i++) indexs[i] = i;

    //dane do wykresów z procesu uczenia
    int graphPointsIterator = 0;
    double** globalErrors = new double*[100];
    double** accuracyTestSet = new double*[100];
    double** accuracyLearnSet = new double*[100];
    for(int i = 0; i < 100; i++){
        globalErrors[i] = new double[2];
        accuracyTestSet[i] = new double[2];
        accuracyLearnSet[i] = new double[2];
    }

    //uczenie
    system_clock::time_point start = system_clock::now();

    for(int i = 0; i < noOfIterations; i++){
        if(randomFlag)
            random_shuffle(indexs, indexs + inputsLearnData.size());

        double globalError = 0;
        //EPOKA
        for(int j = 0; j < inputsLearnData.size(); j++){
            per->learn(inputsLearnData[indexs[j]], outputsLearnData[indexs[j]]);
            globalError += per->getCost();
        }
        //tak często, aby wyszło 100 razy na przestrzeni wszystkich iteracji
        if(i % (noOfIterations / 100) == 0){
            globalErrors[graphPointsIterator][0] =
            accuracyTestSet[graphPointsIterator][0] =
            accuracyLearnSet[graphPointsIterator][0] = i;
            globalErrors[graphPointsIterator][1] = globalError;
            accuracyLearnSet[graphPointsIterator][1] = accuracyTest(per, inputsLearnData, outputsLearnData);
            accuracyTestSet[graphPointsIterator][1] = accuracyTest(per, inputsTestData, outputsTestData);
            cout << i << "\t"
                 << globalError << "\t"
                 << accuracyLearnSet[graphPointsIterator][1] << "\t"
                 << accuracyTestSet[graphPointsIterator][1] << endl;
            graphPointsIterator++;
        }
    }
    cout << endl;

    //wypisanie czasu trwania nauki
    cout << "czas nauki: "
         << duration_cast<milliseconds>(system_clock::now() - start).count()
         << "ms" << endl << endl;

    //rysowanie wykresów
    char c;
    gnuplot << "set xlabel \"numer epoki\""; gnuplot.execute();
    gnuplot << "set ylabel \"błąd globalny\""; gnuplot.execute();
    gnuplot.addElements(globalErrors, globalErrors + 100, "with points pt 22 ps 1", "err");
    gnuplot.execute();
    cin >> c;
    gnuplot << "set xlabel \"numer epoki\""; gnuplot.execute();
    gnuplot << "set ylabel \"% zakwalifikowanych wzorców uczących\""; gnuplot.execute();
    gnuplot.addElements(accuracyLearnSet, accuracyLearnSet + 100, "with points pt 22 ps 1", "learn");
    gnuplot.execute();
    cin >> c;
    gnuplot << "set xlabel \"numer epoki\""; gnuplot.execute();
    gnuplot << "set ylabel \"% zakwalifikowanych wzorców testowych\""; gnuplot.execute();
    gnuplot.addElements(accuracyTestSet, accuracyTestSet + 100, "with points pt 22 ps 1", "test");
    gnuplot.execute();
    cin >> c;

    //zwolnienie wykorzystywanej pamieci
    for(int i = 0; i < 100; i++){
        delete[] globalErrors[i];
        delete[] accuracyTestSet[i];
        delete[] accuracyLearnSet[i];
    }
    delete[] globalErrors;
    delete[] accuracyTestSet;
    delete[] accuracyLearnSet;

    delete[] indexs;

    //testowanie perceptronu----------------------------------
    //macierz pomylek
    vector<vector<int>> confusionMatrix(
            per->getNoOfOutputs(),
            vector<int>(per->getNoOfOutputs(), 0));

    //testowanie danych - obliczenie błędu globalnego i macierzy pomyłek
    double globalError = 0;
    for(int i = 0; i < inputsTestData.size(); i++){
        const double* outputs = per->test(inputsTestData[i], outputsTestData[i]);
        int foundClass = checkClass(outputs, per->getNoOfOutputs());
        int realClass = checkClass(outputsTestData[i], per->getNoOfOutputs());
        confusionMatrix[realClass][foundClass]++;
        globalError += per->getCost();
    }

    //wypisanie macierzy pomylek
    cout << "Macierz pomyłek:" << endl;
    printMatrix(confusionMatrix);
    cout << endl << endl;

    //wyliczenie i wypisanie błędów pierwszego i drugiego rodzaju,
    //oraz liczby poprawnie zakwalifkowanych danych na podstawie macierzy pomyłek
    int qualifiedCorrectly = 0;
    for(unsigned int i = 0; i < confusionMatrix.size(); i++){
        cout << "Klasa " << i << endl;

        //poprawna klasyfikacja
        qualifiedCorrectly += confusionMatrix[i][i];
        cout << "\tzakwalifikowano poprawnie: " << confusionMatrix[i][i] << endl;

        //błędy pierwszego rodzaju (odrzucamy to co jest prawdą - wyszło, że nie należy a należy)
        int falsePositives = 0;
        for(unsigned int column = 0; column < confusionMatrix.size(); column++){
            if(column != i)
                falsePositives += confusionMatrix[i][column];
        }
        cout << "\tbłędy pierwszego rodzaju: " << falsePositives << endl;

        //błędy drugiego rodzaju (nie odrzucamy tego, co jest fałszem - wyszło, że należy a nie należy)
        int falseNegatives = 0;
        for(unsigned int row = 0; row < confusionMatrix.size(); row++){
            if(row != i)
                falseNegatives += confusionMatrix[row][i];
        }
        cout << "\tbłędy drugiego rodzaju: " << falseNegatives << endl;
        cout << endl;
    }

    cout << "razem zakwalifkowano poprawnie: " << qualifiedCorrectly << "/" << inputsTestData.size() << endl;

    delete per;
}