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

    double minimum();

    double maksimum();

    double rozstep();

    double kwartyl_1();

    double mediana();

    double kwartyl_3();

    double harmoniczna();

    double geometryczna();

    double arytmetyczna();

    double potegowa_2();

    double potegowa_3();

    double wariancja();

    double odchylenie();

    double kurtoza();
};

typedef shared_ptr<Proba> Proba_ptr;

#endif //IAD_1_PROBA_H
