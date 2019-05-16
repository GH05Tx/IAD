//
// Created by Maciej Pracucik on 16.05.2019.
//

#ifndef UNTITLED2_SPACE_H
#define UNTITLED2_SPACE_H

#include <iostream>
#include <vector>
#include <string>

class Space{
private:
    const int dim;
    std::vector<double*> elements;
public:
    Space(const Space& space) = delete;
    void operator=(const Space& space) = delete;

    Space(int dimension);

    Space(int dimension, std::istream& is, int noOfColumns, std::vector<int> selectedColumns = {}, bool (*pred)(std::string*)=[](std::string*)->bool{return true;});

    ~Space();

    void addElement(double* element);

    int dimension() const{
        return dim;
    }

    int size() const{
        return elements.size();
    }

    const double* operator[](int i) const{
        return elements[i];
    }

    double* const* begin(){
        return elements.data();
    }

    double* const* end(){
        return elements.data() + elements.size();
    }

    double distance(const double* a, const double* b) const;

};


#endif //UNTITLED2_SPACE_H
