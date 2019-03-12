//
// Created by Jasiek on 07.03.2019.
//

#ifndef IAD_1_PROBA_H
#define IAD_1_PROBA_H

#include <iostream>
#include <memory>
#include <vector>

using namespace std;

class Proba {
private:
    vector<float> dane;
public:
    Proba() = default;

    Proba(vector<float> &);

    ~Proba() = default;

    void wyswietl();

    float minimum();

    float maksimum();

    float rozstep();

    float kwartyl_1();

    double mediana();

    float kwartyl_3();

    double harmoniczna();

    double geometryczna();

    float arytmetyczna();

    double potegowa_2();

    double potegowa_3();

    double potegowa(int);

    float wariancja();

    float odchylenie();

    float kurtoza();
};

typedef shared_ptr<Proba> Proba_ptr;

#endif //IAD_1_PROBA_H
