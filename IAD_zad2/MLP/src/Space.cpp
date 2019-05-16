//
// Created by Maciej Pracucik on 16.05.2019.
//

#include "../include/Space.h"
#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <cmath>
using namespace std;

Space::Space(int dim) : dim(dim){}

Space::Space(int dim, istream& is, int noOfColumns, std::vector<int> selectedColumns, bool (*pred)(string*)) : dim(dim){
    is.clear();
    is.seekg(0, is.beg);
    string* features = new string[noOfColumns];
    char* buffer = new char[50];
    int i = 0;
    while(is >> buffer){
        features[i].assign(buffer);
        if(i == (noOfColumns - 1) && pred(features)){
            double* element = new double[dim];
            if(selectedColumns.empty()){
                for(int column = 0; column < noOfColumns; column++){
                    element[column] = stod(features[column]);
                }
            }else{
                for(unsigned int column = 0; column < selectedColumns.size(); column++){
                    element[column] = stod(features[selectedColumns[column]]);
                }
            }
            elements.push_back(element);
        }
        i = (i + 1) % noOfColumns;
    }
    delete[] features;
    delete[] buffer;
}

Space::~Space(){
    for(double* element : elements){
        delete[] element;
    }
}

void Space::addElement(double* element){
    elements.push_back(element);
}

double Space::distance(const double* a, const double* b) const{
    double sum = 0;
    for(int i = 0; i < dim; i++){
        sum += pow(a[i] - b[i], 2.0);
    }
    return sqrt(sum);
}