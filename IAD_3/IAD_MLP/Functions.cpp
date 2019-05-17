//
// Created by Jasiek on 17.05.2019.
//

#include "Functions.h"
#include "Functions.h"

#pragma once
#include <cmath>

double SigmoidFun::execute(double val)
{
    return 1.0 / (1.0 + exp(-beta*val));
}
double SigmoidFun::derivative(double val)
{
    double f = execute(val);
    return beta*(1.0 - f)*f;
}

double TanghFun::execute(double val)
{
    return tanh(beta*val);
}
double TanghFun::derivative(double val)
{
    return beta*(1 - pow(execute(val), 2));
}

double ErrorFunction::SumOfSquares(const std::vector<double>& values)
{
    double sum = 0;
    for (const double& val : values)
    {
        sum += pow(val,2);
    }
    return sum;
}

double RMS::Calculate(const std::vector<double>& differences)
{
    double result = SumOfSquares(differences);
    result *= 1.0/differences.size();
    result = sqrt(result);
    return result;
}

double MSE::Calculate(const std::vector<double>& differences)
{
    double result = SumOfSquares(differences);
    result *= 1.0 / differences.size();
    return result;
}

double DirectOutputFun::execute(double val)
{
    return val;
}
double DirectOutputFun::derivative(double val)
{
    return 1;
}
