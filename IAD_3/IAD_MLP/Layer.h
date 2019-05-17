//
// Created by Jasiek on 17.05.2019.
//

#ifndef IAD_MLP_LAYER_H
#define IAD_MLP_LAYER_H

#pragma once
#include <vector>
#include <assert.h>
#include "Neuron.h"
#include "Bias.h"
using namespace std;

class Layer {
protected:
    vector<Neuron*> neurons;
    bool biasCreated = false;

public:
    Layer();
    Layer(unsigned neuronsNumber, unsigned inputsNumber);
    Layer(unsigned neuronsNumber, unsigned inputsNumber, Function& funPack);
    ~Layer();

    virtual void FeedData(const vector<double>& data);
    void BackPropagation(const vector<double>& differences);
    vector<double> GetOutput() const;
    vector<vector<double>> GetInputWeights() const;
    bool IsBiasCreated() const;
    void AddBias();
    unsigned GetNumberOfNeurons()const;
    void UpdateWeights();
    void UpdateEta(double value);
    void UpdateAlfa(double value);
};




#endif //IAD_MLP_LAYER_H
