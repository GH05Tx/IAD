//
// Created by Jasiek on 11.03.2019.
//

#ifndef IAD_1_DANE_H
#define IAD_1_DANE_H

#include <iostream>
#include <vector>
#include <memory>

using namespace std;

class Dane {
protected:
    vector<float> sepalLength;
    vector<float> sepalWidth;
    vector<float> petalLength;
    vector<float> petalWidth;
    string gatunek;
public:
    virtual void wczytaj() = 0;

    void printSL();

    void printSW();

    void printPL();

    void printPW();

    vector<float> getSL();

    vector<float> getSW();

    vector<float> getPL();

    vector<float> getPW();
};

typedef shared_ptr<Dane> Dane_ptr;

#endif //IAD_1_DANE_H
