//
// Created by Jasiek on 26.03.2019.
//

#include <iostream>
#include "../include/Punkt.h"

Punkt::Punkt(vector<double> val, int klaster) {
    this->values = val;
    this->klaster = klaster;
}

vector<double> Punkt::getValues() {
    return values;
}

Pkt_ptr Punkt::getPkt() {
    Pkt_ptr punkt(new Punkt(values, klaster));
    return punkt;
}

void Punkt::printPunkt() {
    for (int i = 0; i < values.size(); i++) {
        cout << values[i] << " ";
    }
    cout << endl;
}

int Punkt::getKlaster() {
    return klaster;
}

void Punkt::setKlaster(int klaster) {
    this->klaster = klaster;
}