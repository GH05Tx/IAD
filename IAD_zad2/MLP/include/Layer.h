//
// Created by Maciej Pracucik on 16.05.2019.
//

#ifndef UNTITLED2_LAYER_H
#define UNTITLED2_LAYER_H

#include <iostream>

class Layer {
    double **neurons;
    double *stimulations;
    double *outputs;
    double *inputs;
    double *gradient;
    double *previousErrors;
    int noOfOutputs;
    int noOfInputs;

    double learningSpeed;
    bool biasFlag;
    double momentum;

    double (*activationFunction)(double);
    double (*derivativeOfActivationFunction)(double);

    static double stepFunction(double d);
    static double derivativeOfStepFunction(double d);
    static double sigmoidalFunction(double d);
    static double derivativeOfSigmoidalFunction(double d);
    static double identityFunction(double d);
    static double derivativeOfIdentityFunction(double d);
    static double hiperbolicTangentFunction(double d);
    static double derivativeOfHiperbolicTangentFunction(double d);

public:
    Layer(int noOfOutputs, int noOfInputs, bool biasFlag, std::istream* is);

    ~Layer();

    Layer(const Layer& Layer) = delete;

    void saveToStream(std::ostream& os);

    int getNoOfOutputs() const{
        return noOfOutputs;
    }

    int getNoOfInputs() const{
        return noOfInputs;
    }

    double getLearningSpeed() const{
        return learningSpeed;
    }

    void setLearningSpeed(double learningSpeed){
        this->learningSpeed = learningSpeed;
    }

    double getMomentum() const{
        return momentum;
    }

    void setMomentum(double momentum){
        this->momentum = momentum;
    }

    const double* test(const double* in);

    void learn(const double* err);

    const double* calculatePreviousErrors(const double* err);
};


#endif //UNTITLED2_LAYER_H
