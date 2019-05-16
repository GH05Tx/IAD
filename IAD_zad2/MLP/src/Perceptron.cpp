//
// Created by Maciej Pracucik on 16.05.2019.
//

#include "../include/Perceptron.h"
#include <iostream>
using namespace std;

//zaklada poprawnosc 'layersDescription' (przynajmniej dwie wartosci musza byc)
//w obiekcie warstwami nazywami tylko warstwy przetwarzajace, liczba neuronow pierwszej
//podanej warstwy jest interpretowana jako liczba wejsc
//liczba podanych flag biasu jest zatem o jeden mniejsza od liczby podanych warstw
Perceptron::Perceptron(vector<int> layersDescription, vector<bool> biasFlags, istream* is) :
        learningSpeed(0),
        noOfLayers(layersDescription.size() - 1),
        noOfInputs(layersDescription[0]){
    layers = new Layer*[noOfLayers];
    vector<int>::iterator iter = layersDescription.begin();
    iter++;
    for(int i = 0; i < noOfLayers; i++){
        if(i == 0){
            layers[i] = new Layer(*iter, noOfInputs, biasFlags[i], is);
        }else{
            layers[i] = new Layer(*iter, layers[i - 1]->getNoOfOutputs(), biasFlags[i], is);
        }
        iter++;
    }

    noOfOutputs = layers[noOfLayers - 1]->getNoOfOutputs();
}

Perceptron::~Perceptron(){
    for(int i = 0; i < noOfLayers; i++){
        delete layers[i];
    }
    delete[] layers;
}

void Perceptron::saveToStream(ostream& os){
    for(int i = 0; i < noOfLayers; i++){
        layers[i]->saveToStream(os);
        os << "\n" << endl;
    }
}

const double* Perceptron::test(const double* inputs){
    //propagacja wprzód
    const double* layerOutputs = inputs;
    for(int i = 0; i < noOfLayers; i++){
        layerOutputs = layers[i]->test(layerOutputs);
        //-----
        cout << "warstwa " << i << " ";
        cout << "[";
        for(int o = 0; o < layers[i]->getNoOfOutputs(); o++){
            cout << layerOutputs[o] << " ";
        }
        cout << "]";
        cout << endl;
        //-----
    }
    return layerOutputs;
}

const double* Perceptron::test(const double* inputs, const double* expectedOutputs){
    //propagacja wprzód
    const double* layerOutputs = inputs;
    for(int i = 0; i < noOfLayers; i++){
        layerOutputs = layers[i]->test(layerOutputs);
    }

    //błędy ostatniej warstwy
    cost = 0;
    for(int i = 0; i < noOfOutputs; i++){
        double error = expectedOutputs[i] - layerOutputs[i];
        cost += error * error;
    }

    return layerOutputs;
}

void Perceptron::learn(const double* inputs, const double* expectedOutputs){
    //propagacja wprzód
    const double* layerOutputs = inputs;
    for(int i = 0; i < noOfLayers; i++){
        layerOutputs = layers[i]->test(layerOutputs);
    }

    //błędy ostatniej warstwy i wartość funkcji kosztu
    cost = 0;
    double* const errors = new double[noOfOutputs];
    for(int i = 0; i < noOfOutputs; i++){
        errors[i] = expectedOutputs[i] - layerOutputs[i];
        cost += errors[i] * errors[i];
    }

    //propagacja błedów wstecz i modyfikacja wag
    //(ważne aby najpierw wyliczyć błąd poprzedniej
    //warstwy a dopiero później modyfikować wagi)
    const double* layerErrors = errors;
    const double* previousErrors;
    for(int i = noOfLayers - 1; i >= 0; i--){
        if(i > 0)
            previousErrors = layers[i]->calculatePreviousErrors(layerErrors);
        layers[i]->learn(layerErrors);
        layerErrors = previousErrors;
    }

    delete[] errors;
}