//
// Created by Maciej Pracucik on 16.05.2019.
//

#include "../include/Layer.h"
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
using namespace std;

Layer::Layer(int noOfOutputs, int noOfInputs, bool biasFlag, istream* is) :
        noOfOutputs(noOfOutputs),
        noOfInputs(noOfInputs),
        learningSpeed(0),
        biasFlag(biasFlag),
        momentum(0),
        activationFunction(sigmoidalFunction),
        derivativeOfActivationFunction(derivativeOfSigmoidalFunction){

    neurons = new double*[noOfOutputs];
    for(int o = 0; o < noOfOutputs; o++){
        neurons[o] = new double[noOfInputs + biasFlag];
        for(int i = 0; i < noOfInputs + biasFlag; i++){
            if(is == nullptr)
                neurons[o][i] = (rand() / (double)RAND_MAX) - 0.5;
            else
                (*is) >> neurons[o][i];
        }
    }
    stimulations = new double[noOfOutputs];
    outputs = new double[noOfOutputs];
    inputs = new double[noOfInputs];
    gradient = new double[noOfOutputs * (noOfInputs + biasFlag)];
    memset(gradient, 0, sizeof(double) * noOfOutputs * (noOfInputs + biasFlag));
    previousErrors = new double[noOfInputs];
}

Layer::~Layer(){
    for(int o = 0; o < noOfOutputs; o++){
        delete[] neurons[o];
    }
    delete[] neurons;
    delete[] stimulations;
    delete[] outputs;
    delete[] inputs;
    delete[] gradient;
    delete[] previousErrors;
}

void Layer::saveToStream(ostream& os){
    for(int o = 0; o < noOfOutputs; o++){
        for(int i = 0; i < noOfInputs + biasFlag; i++){
            os << neurons[o][i] << " ";
        }
        os << "\n";
    }
}

const double* Layer::test(const double* in){
    for(int i = 0; i < noOfInputs; i++){
        inputs[i] = in[i];
    }
    for(int o = 0; o < noOfOutputs; o++){
        stimulations[o] = 0;
        for(int i = 0; i < noOfInputs; i++){
            stimulations[o] += inputs[i] * neurons[o][i];
        }
        if(biasFlag){
            stimulations[o] += neurons[o][noOfInputs];
        }
        outputs[o] = activationFunction(stimulations[o]);
    }
    return outputs;
}

void Layer::learn(const double* err){
    for(int o = 0; o < noOfOutputs; o++){
        double factor = learningSpeed * err[o] *
                        derivativeOfActivationFunction(stimulations[o]);
        for(int i = 0; i < noOfInputs; i++){
            int weightIndex = o * (noOfInputs + biasFlag) + i;
            gradient[weightIndex] = factor * inputs[i] + momentum * gradient[weightIndex];
            neurons[o][i] += gradient[weightIndex];
        }
        if(biasFlag){
            int weightIndex = o * (noOfInputs + biasFlag) + noOfInputs;
            gradient[weightIndex] = factor + momentum * gradient[weightIndex];
            neurons[o][noOfInputs] += gradient[weightIndex];
        }
    }
}

const double* Layer::calculatePreviousErrors(const double* err){
    for(int i = 0; i < noOfInputs; i++){
        previousErrors[i] = 0;
        for(int o = 0; o < noOfOutputs; o++){
            previousErrors[i] += err[o] * derivativeOfActivationFunction(stimulations[o]) * neurons[o][i];
        }
    }
    return previousErrors;
}

double Layer::identityFunction(double d){
    return d;
}

double Layer::derivativeOfIdentityFunction(double d){
    return 1;
}

double Layer::sigmoidalFunction(double d){
    return 1.0 / (1 + exp(-d));
}

double Layer::derivativeOfSigmoidalFunction(double d){
    return sigmoidalFunction(d) * (1 - sigmoidalFunction(d));
}

double Layer::hiperbolicTangentFunction(double d){
    return exp(d) - exp(-d) / (exp(d) + exp(-d));
}

double Layer::derivativeOfHiperbolicTangentFunction(double d){
    return 1 - pow(hiperbolicTangentFunction(d), 2);
}
