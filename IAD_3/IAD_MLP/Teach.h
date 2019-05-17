//
// Created by Jasiek on 17.05.2019.
//

#ifndef IAD_MLP_TEACH_H
#define IAD_MLP_TEACH_H
#pragma once
#include "Service.h"

class Teach : public Service
{
public:
	Teach(Net& network) : Service(network){ }
	virtual void Execute()override
	{
		assert(inputValues.size() == targetValues.size()); //wektory input i output muszą być równe.
		for (unsigned i = 0; i < NumberOfIterations && lastError>ErrorLimit; i++)
		{
			teach();		
			iterations++;
			errors.push_back(lastError);
		}
	}

	void FeedData(const std::vector<double>& input, const std::vector<double>& targetOutput)
	{
		assert(input.size() == network.GetInputsNumber());
		assert(targetOutput.size() == network.GetOutputsNumber());
		inputValues.push_back(input);
		targetValues.push_back(targetOutput);
	}

	void FeedData(const std::vector<std::vector<double>>& inputs, const std::vector<std::vector<double>>& targetVals)
	{
		assert(inputs.size() == targetVals.size());
		unsigned length = inputs.size();
		for (unsigned i = 0; i < length-1; i++)
		{
			FeedData(inputs[i], targetVals[i]);
		}
	}
	unsigned NumberOfIterations = 200;
	double ErrorLimit = 0.000;
	double GetError() { return lastError; }
	unsigned GetIterationsCount() { return iterations; }
	std::vector<double> allerrors() { return errors; }
	~Teach(){}
private:
	unsigned iterations = 0;
	std::vector<double> errors;
	double lastError = 100;
	std::vector<std::vector<double>> inputValues;
	std::vector<std::vector<double>> targetValues;
	

	void teach()
	{
		unsigned length = inputValues.size();
		for (unsigned i = 0; i < length; i++)
		{
			network.FeedData(inputValues[i]);
			network.BackPropagation(targetValues[i]);
		}
		lastError = network.GetError();
	}
};
#endif //IAD_MLP_TEACH_H
