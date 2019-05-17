//
// Created by Jasiek on 17.05.2019.
//

#ifndef IAD_MLP_BIAS_H
#define IAD_MLP_BIAS_H
#pragma once
#include "Neuron.h"
using namespace std;

class Bias : public Neuron
{
public:
	Bias();
	~Bias()=default;

	virtual void FeedData(const vector<double>& data)override;
	virtual void FeedData(const double& val);
	virtual double GetOutput()override;
};


#endif //IAD_MLP_BIAS_H
