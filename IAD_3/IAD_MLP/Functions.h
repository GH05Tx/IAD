//
// Created by Jasiek on 17.05.2019.
//

#ifndef IAD_MLP_FUNCTIONS_H
#define IAD_MLP_FUNCTIONS_H

#pragma once
#include <cmath>
#include <vector>
using namespace std;

class Function
{
public:
    virtual double execute(double val) = 0;
    virtual double derivative(double val) = 0;
};

class ErrorFunction
{
public:
    virtual double Calculate(const vector<double>& differences) = 0;
protected:
    double SumOfSquares(const vector<double>& values);
};

class RMS : public ErrorFunction
{
    virtual double Calculate(const vector<double>& differences)override;
};

class MSE : public ErrorFunction
{
    virtual double Calculate(const vector<double>& differences)override;
};

class SigmoidFun : public Function
{
public:
    SigmoidFun(double beta) : beta(beta) {}
    double execute(double val)override;
    double derivative(double val)override;
private:
    double beta;
};

class TanghFun : public Function
{
public:
    TanghFun(double beta) : beta(beta) {}
    double execute(double val)override;
    double derivative(double val)override;
private:
    double beta;
};

class DirectOutputFun : public Function
{
    double execute(double val)override;
    double derivative(double val)override;
};

class Functions
{
private:
    Functions() :
            Sigmoid(1.0),
            Tangh(1.0) {}
public:
    static Functions& getInstance()
    {
        static Functions instance;
        return instance;
    }

    Functions(Functions&) = delete;
    void operator=(Functions&) = delete;

public:
    SigmoidFun Sigmoid;
    TanghFun Tangh;
    DirectOutputFun DirectOutput;
    RMS RMS;
    MSE MSE;
};




#endif //IAD_MLP_FUNCTIONS_H
