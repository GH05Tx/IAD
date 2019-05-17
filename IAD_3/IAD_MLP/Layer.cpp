//
// Created by Jasiek on 17.05.2019.
//

#include "Layer.h"

Layer::Layer()
{

}

Layer::Layer(unsigned neuronsNumber, unsigned inputsNumber)
{
    neurons.reserve(neuronsNumber);
    for (unsigned int i = 0; i < neuronsNumber; i++)
    {
        neurons.push_back(new Neuron(inputsNumber));
    }
}

Layer::Layer(unsigned neuronsNumber, unsigned inputsNumber, Function& funPack)
{
    neurons.reserve(neuronsNumber);
    for (unsigned int i = 0; i < neuronsNumber; i++)
    {
        neurons.push_back(new Neuron(funPack, inputsNumber));
    }
}

Layer::~Layer()
{
    for (Neuron* neu : neurons)
    {
        delete neu;
    }
}

std::vector<double> Layer::GetOutput()const
{
    int me = 0;
    std::vector<double> result;
    result.reserve(neurons.size());
    for (Neuron* const neuron : neurons)
    {
        result.push_back(neuron->GetOutput());
    }
    return result;
}

bool Layer::IsBiasCreated()const
{
    return biasCreated;
}

void Layer::FeedData(const std::vector<double>& data)
{
    unsigned length = neurons.size() - (int)biasCreated;
    for (unsigned i = 0; i < length; i++)
    {
        neurons[i]->FeedData(data);
    }
}

std::vector<std::vector<double>> Layer::GetInputWeights() const
{
    std::vector<std::vector<double>> result;
    result.reserve( GetNumberOfNeurons() - (int)IsBiasCreated() );
    for (Neuron* neuron : neurons)
    {
        result.push_back(neuron->GetInputWeights());
    }
    return result;
}

unsigned Layer::GetNumberOfNeurons()const
{
    return neurons.size();
}

void Layer::UpdateWeights()
{
    for (Neuron* neuron : neurons)
    {
        neuron->UpdateWeights();
    }
}

void Layer::UpdateEta(double value)
{
    for (Neuron* neuron : neurons)
    {
        neuron->SetEta(value);
    }
}

void Layer::UpdateAlfa(double value)
{
    for (Neuron* neuron : neurons)
    {
        neuron->SetAlfa(value);
    }
}

void Layer::BackPropagation(const std::vector<double>& values)
{
    unsigned length = values.size();
    for (unsigned i = 0; i < length; i++)
    {
        neurons[i]->SetDifference(values[i]);
    }
}

void Layer::AddBias()
{
    if (!biasCreated)
    {
        neurons.push_back(new Bias());
        biasCreated = true;
    }
}