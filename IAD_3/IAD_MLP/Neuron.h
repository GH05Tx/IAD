//
// Created by Jasiek on 17.05.2019.
//

#ifndef IAD_MLP_NEURON_H
#define IAD_MLP_NEURON_H

#pragma once
#include <vector>
#include "Functions.h"
using namespace std;

class Neuron {
protected:
    vector<double> inputWeights;
    vector<double> lastInputs;
    double output;
    Function& functions;
    void setRandomWeights(unsigned number);
    double difference; //needed for back propagation.
    vector<double> previousWeightsDeltas;
    double lastWeightedSum = 0;

    double eta = 0.1;
    double alfa = 0.1; //0.86 jest IDEALNE dla XOR... 100 iteracji eta =0.1

public:
    Neuron(Function& functionsPack, unsigned inputsNumber);
    Neuron(unsigned inputsNumber);
    ~Neuron();

    virtual void FeedData(const vector<double>& data);
    virtual void FeedData(const double& val);
    virtual double GetOutput();
    const vector<double>& GetInputWeights()const;
    void SetDifference(double value);
    void UpdateWeights();
    void SetEta(double value) { eta = value; }
    void SetAlfa(double value) { alfa = value; }
};




#endif //IAD_MLP_NEURON_H
