//
// Created by Jasiek on 17.05.2019.
//
#include "Neuron.h"
#include <assert.h>


Neuron::Neuron(Function& funPack, unsigned inputsNumber) : functions(funPack)
{
    inputWeights.resize(inputsNumber);
    previousWeightsDeltas.resize(inputsNumber);
    setRandomWeights(inputsNumber);
}

Neuron::Neuron(unsigned inputsNumber) : functions(Functions::getInstance().Sigmoid)
{
    inputWeights.resize(inputsNumber);
    previousWeightsDeltas.resize(inputsNumber);
    setRandomWeights(inputsNumber);
}

Neuron::~Neuron()
{

}

void Neuron::FeedData(const std::vector<double>& data)
{
    lastInputs = data;
    double sum = 0;
    assert(data.size() == inputWeights.size());
    unsigned int length = inputWeights.size();
    for (unsigned int i = 0; i < length; i++)
    {
        sum += inputWeights[i] * data[i];
    }
    lastWeightedSum = sum;
    output = functions.execute(sum);
}

void Neuron::FeedData(const double& val)
{
    output = functions.execute(val);
}

double Neuron::GetOutput()
{
    return output;
}

const std::vector<double>& Neuron::GetInputWeights()const
{
    return inputWeights;
}

void Neuron::SetDifference(double value)
{
    difference = value;
}

void Neuron::UpdateWeights()
{
    unsigned length = inputWeights.size();
    double currentDelta;
    for (unsigned i=0; i<length; i++)
    {
        currentDelta = eta * difference * functions.derivative(lastWeightedSum) * lastInputs[i]
                       + alfa*previousWeightsDeltas[i];
        inputWeights[i] += currentDelta;
        previousWeightsDeltas[i] = currentDelta;
    }
}

void Neuron::setRandomWeights(unsigned inputsNumber)
{
    for (unsigned i = 0; i < inputsNumber; i++)
    {
        inputWeights[i] = (double(rand()) / RAND_MAX);
    }
}
