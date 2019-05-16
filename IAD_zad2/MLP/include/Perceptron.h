//
// Created by Maciej Pracucik on 16.05.2019.
//

#ifndef UNTITLED2_PERCEPTRON_H
#define UNTITLED2_PERCEPTRON_H

#include "Layer.h"
#include <vector>
#include <iostream>

class Perceptron{
    Layer** layers;
    double learningSpeed;
    double momentum;
    double cost;

    int noOfLayers;
    int noOfOutputs;
    int noOfInputs;
public:
    Perceptron(std::vector<int> layersDescription, std::vector<bool> biasFlags, std::istream* is = nullptr);
    ~Perceptron();

    Perceptron(const Perceptron&) = delete;
    Perceptron& operator=(const Perceptron&) = delete;

    void saveToStream(std::ostream& os);

    double getLearningSpeed(){
        return learningSpeed;
    }

    void setLearningSpeed(double learningSpeed){
        this->learningSpeed = learningSpeed;
        for(int i = 0; i < noOfLayers; i++){
            layers[i]->setLearningSpeed(learningSpeed);
        }
    }

    double getMomentum(){
        return momentum;
    }

    void setMomentum(double momentum){
        this->momentum = momentum;
        for(int i = 0; i < noOfLayers; i++){
            layers[i]->setMomentum(momentum);
        }
    }

    double getCost(){
        return cost;
    }

    int getNoOfLayers(){
        return noOfLayers;
    }

    int getNoOfOutputs(){
        return noOfOutputs;
    }

    int getNoOfInputs(){
        return noOfInputs;
    }

    //sprawdzenie reakcji sieci na wzorzec
    const double* test(const double* inputs);

    //sprawdzenie reakcji i obliczenie błędu
    const double* test(const double* inputs, const double* expectedOutputs);

    //sprawdzenie reakcji sieci, obliczenie błędu i modyfikacja wag
    void learn(const double* inputs, const double* expectedOutputs);
};


#endif //UNTITLED2_PERCEPTRON_H
