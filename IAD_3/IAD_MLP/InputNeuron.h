//
// Created by Jasiek on 17.05.2019.
//

#ifndef IAD_MLP_INPUTNEURON_H
#define IAD_MLP_INPUTNEURON_H
#pragma once
#include "Neuron.h"
#include <assert.h>

class InputNeuron : public Neuron
{
public:
	InputNeuron() : Neuron(1) {}
	~InputNeuron() {}
	void FeedData(const std::vector<double>& data)override
	{
		assert(data.size() == 1);
		output = data[0];
	}

	void FeedData(const double& val)override
	{
		output = val;
	}
};

#endif //IAD_MLP_INPUTNEURON_H
