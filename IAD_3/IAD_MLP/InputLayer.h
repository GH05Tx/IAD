//
// Created by Jasiek on 17.05.2019.
//

#ifndef IAD_MLP_INPUTLAYER_H
#define IAD_MLP_INPUTLAYER_H
#pragma once

#include "Layer.h"
#include "InputNeuron.h"
using namespace std;

class InputLayer : public Layer
{
public:
	InputLayer(unsigned int neuronsNumber)
	{
		neurons.reserve(neuronsNumber);
		for (unsigned i = 0; i < neuronsNumber; i++)
		{
			neurons.push_back(new InputNeuron());
		}
	}

	void FeedData(const vector<double>& data)override
	{
		unsigned length = data.size();
		for (unsigned i = 0; i < length; i++)
		{
			neurons[i]->FeedData(data[i]);
		}
	}
};
#endif //IAD_MLP_INPUTLAYER_H
