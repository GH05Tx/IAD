//
// Created by Jasiek on 26.03.2019.
//

#ifndef ZAD_2_PUNKT_H
#define ZAD_2_PUNKT_H

#include <vector>
#include <memory>

using namespace std;

class Punkt;

typedef shared_ptr<Punkt> Pkt_ptr;

class Punkt {
private:
    vector<double> values;
    int klaster;
public:
    Punkt(vector<double>, int);

    vector<double> getValues();

    Pkt_ptr getPkt();

    void printPunkt();

    int getKlaster();

    void setKlaster(int);
};

#endif //ZAD_2_PUNKT_H
