//
// Created by Jasiek on 17.05.2019.
//

#include "Net.h"

Net::Net(const std::vector<unsigned> Topology) : errorFunction(Functions::getInstance().MSE)
{
    unsigned int layersNumber = Topology.size();
    layers.reserve(layersNumber);
    layers.push_back(new InputLayer(Topology[0]));
    layers.back()->AddBias();	//BIAS ADDED TO INPUT LAYER
    for (unsigned i = 1; i < layersNumber - 1; i++)
    {
        layers.push_back(new Layer(Topology[i], layers.back()->GetNumberOfNeurons()));
        layers.back()->AddBias();
    }
    layers.push_back(new Layer(Topology[layersNumber-1], layers.back()->GetNumberOfNeurons(), Functions::getInstance().DirectOutput)); //Output without BIAS
}

Net::~Net()
{
    for (Layer* layer : layers)
    {
        delete layer;
    }
}

unsigned Net::GetInputsNumber()const
{
    return layers[0]->GetNumberOfNeurons() - (int)layers[0]->IsBiasCreated();
}

unsigned Net::GetOutputsNumber()const
{
    return layers.back()->GetNumberOfNeurons() - (int)layers.back()->IsBiasCreated();
}

void Net::FeedData(const std::vector<double> data)
{
    layers.front()->FeedData(data);

    unsigned int length = layers.size();
    for (unsigned int i = 1; i < length; i++)
    {
        layers[i]->FeedData(layers[i - 1]->GetOutput());
    }
}



void Net::FeedData(const std::vector<double> data, const std::vector<double> expected)
{
    FeedData(data);

    std::vector<double> diffrences;
    std::vector<double> currentOutput = layers.back()->GetOutput();
    unsigned length = expected.size();
    diffrences.reserve(length);

    for (unsigned i = 0; i < length; i++)
    {
        diffrences.push_back(expected[i] - currentOutput[i]);
    }
    CalculateError(diffrences);
}

std::string Net::toString()
{
    std::string result;
    for (Layer* layer : layers)
    {
        for (const double& value : layer->GetOutput())
        {
            result += std::to_string(value);
            result += " ";
        }
        result += '\n';
    }
    return result;
}

std::vector<double> Net::Output()
{
    std::vector<double> currentOutput = layers.back()->GetOutput();
    return currentOutput;
}

void Net::SetErrorFunction(ErrorFunction& fun)
{
    errorFunction = fun;
}

void Net::UpdateEta(double value)
{
    for (Layer* layer : layers)
    {
        layer->UpdateEta(value);
    }
}

void Net::UpdateAlfa(double value)
{
    for (Layer* layer : layers)
    {
        layer->UpdateAlfa(value);
    }
}

double Net::GetError()const
{
    return Error;
}

void Net::CalculateError(const std::vector<double>& deltas)
{
    Error = errorFunction.Calculate(deltas);
}


void Net::BackPropagation(const std::vector<double> expectedData)
{
    //Calculate output error.
    std::vector<double> currentOutput = layers.back()->GetOutput();
    std::vector<double> previousDifferences;
    unsigned length = expectedData.size();
    previousDifferences.reserve(length);

    for (unsigned i = 0; i < length; i++)
    {
        previousDifferences.push_back(expectedData[i] - currentOutput[i]);
    }
    CalculateError(previousDifferences);

    //First layer "gradient"
    layers.back()->BackPropagation(previousDifferences);

    //pushing back the error
    unsigned numberOfLayers = layers.size();
    std::vector<std::vector<double>> previousWeights;
    double tempSum = 0;
    std::vector<double> tempDifferences;
    for (unsigned l = numberOfLayers - 2; l > 0; l--) // idziemy od przedostatniej warstwy do 2.
    {
        previousWeights = layers[l + 1]->GetInputWeights();
        unsigned numberOfNeurons = layers[l]->GetNumberOfNeurons() - (int)layers[l]->IsBiasCreated();

        unsigned numberOfNeurons_previous = layers[l + 1]->GetNumberOfNeurons() - (int)layers[l + 1]->IsBiasCreated();
        tempDifferences.resize(numberOfNeurons);
        for (unsigned n = 0; n < numberOfNeurons; n++)
        {
            tempSum = 0;
            for (unsigned w = 0; w < numberOfNeurons_previous; w++)
            {
                tempSum += previousDifferences[w] * previousWeights[w][n];
            }
            tempDifferences[n] = tempSum;
        }
        layers[l]->BackPropagation(tempDifferences);
        previousDifferences = tempDifferences;
    }

    for (unsigned l = 1; l < numberOfLayers; l++)
    {
        layers[l]->UpdateWeights();
    }
}