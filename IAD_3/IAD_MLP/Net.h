//
// Created by Jasiek on 17.05.2019.
//

#ifndef IAD_MLP_NET_H
#define IAD_MLP_NET_H

#pragma once
#include <vector>
#include "Layer.h"
#include "InputLayer.h"
#include "Functions.h"
#include <string>
using namespace std;

class Net {
private:
    vector<Layer*> layers;
    void CalculateError(const vector<double>& differences);
    ErrorFunction& errorFunction;
    double Error = 0;

public:
    Net(vector<unsigned> Topology);
    ~Net();

    void FeedData(const vector<double> data);
    void FeedData(const vector<double> data, const vector<double> expected);
    void BackPropagation(const vector<double> expectedData);
    string toString();
    double GetError()const;
    void SetErrorFunction(ErrorFunction& val);
    unsigned GetInputsNumber()const;
    unsigned GetOutputsNumber()const;
    void UpdateEta(double value);
    void UpdateAlfa(double value);
    vector<double> Output();
};
#endif //IAD_MLP_NET_H
