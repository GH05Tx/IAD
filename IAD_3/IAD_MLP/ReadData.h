//
// Created by Jasiek on 17.05.2019.
//

#ifndef IAD_MLP_READDATA_H
#define IAD_MLP_READDATA_H
#pragma once
#include <tuple>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

tuple<vector<vector<double>>, vector<vector<double>>> ReadData(const int inputsNumber, const int outputsNumber, const string file)
{
	ifstream DataSource(file);
	if (!DataSource.is_open())
	{
		return make_tuple(vector<vector<double>>(), vector<vector<double>>());
	}

	vector<vector<double>> inputs_vector;
	vector<vector<double>> outputs_vector;

	int input_iterator = 0;
	int output_iterator = 0;
	double temp;
	while (!DataSource.eof())
	{
		inputs_vector.push_back(vector<double>());
		outputs_vector.push_back(vector<double>());

		for (input_iterator = 0; input_iterator < inputsNumber; input_iterator++)
		{
			DataSource >> temp;
			inputs_vector.back().push_back(temp);
		}
		for (output_iterator = 0; output_iterator < outputsNumber; output_iterator++)
		{
			DataSource >> temp;
			outputs_vector.back().push_back(temp);
		}
	}

	DataSource.close();
	return make_tuple(inputs_vector, outputs_vector);
}
#endif //IAD_MLP_READDATA_H
