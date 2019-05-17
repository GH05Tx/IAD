//
// Created by Jasiek on 17.05.2019.
//

#include "Bias.h"



Bias::Bias() : Neuron(0) {}

double Bias::GetOutput()
{
	return 1.0;
}

void Bias::FeedData(const std::vector<double>& data)
{
	return;
}

void Bias::FeedData(const double& val)
{
	return;
}
