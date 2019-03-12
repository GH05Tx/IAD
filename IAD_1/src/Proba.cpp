//
// Created by Jasiek on 07.03.2019.
//

#include "../include/Proba.h"
#include <iostream>
#include <memory>
#include <vector>
#include <math.h>

using namespace std;

Proba::Proba(vector<float> &tablica) {
    this->dane = tablica;
}

void Proba::wyswietl() {
    for (int i = 0; i < dane.size(); i++) {
        cout << dane[i] << " ";
    }
}

float Proba::minimum() {
    float min = dane[0];
    for (int i = 1; i < dane.size(); i++) {
        if (dane[i] < min) min = dane[i];
    }
    return min;
}

float Proba::maksimum() {
    float max = dane[0];
    for (int i = 1; i < dane.size(); i++) {
        if (dane[i] > max) max = dane[i];
    }
    return max;
}

float Proba::rozstep() {
    return Proba::maksimum() - Proba::minimum();
}

float Proba::kwartyl_1() {

}

double Proba::mediana() {
    if (dane.size() % 2 == 0) {
        return 0.5 * (dane[(dane.size() + 1) / 2] + dane[dane.size() / 2]);
    }
    if (dane.size() % 2 == 1) {
        return dane[(dane.size() + 1) / 2];
    }
}

float Proba::kwartyl_3() {

}

double Proba::harmoniczna() {
    float suma = 0;
    for (int i = 0; i < dane.size(); i++) {
        suma += 1 / dane[i] * 1.0;
    }
    return dane.size() / suma * 1.0;
}

double Proba::geometryczna() {
    float srednia = 1;
    for (int i = 0; i < dane.size(); i++) {
        srednia *= dane[i];
    }
    return pow(srednia, (1 / 1.0 * dane.size()));
}

float Proba::arytmetyczna() {
    float srednia = 0;
    for (int i = 0; i < dane.size(); i++) {
        srednia += dane[i];
    }
    return srednia / dane.size();
}

double Proba::potegowa_2() {
    float suma = 0;
    for (int i = 0; i < dane.size(); i++) {
        suma += dane[i] * dane[i];
    }
    return pow(suma/dane.size(), 1/2);
}
/*
–1 średnia harmoniczna
0 średnia geometryczna
1 średnia arytmetyczna
2 średnia kwadratowa
*/

double Proba::potegowa_3() {
    float suma=0;
    for(int i=0; i<dane.size(); i++)
    {
        suma+=pow(dane[i],3);
    }
    return pow(suma/dane.size(), 1/3);
}

double Proba::potegowa(int n) {
    float suma = 0;
    for (int i = 0; i < dane.size(); i++) {
        suma += pow(dane[i], n);
    }
    return pow(suma / dane.size(), 1 / n);
}

float Proba::wariancja() {
    float suma = 0, arytmetyczna=Proba::arytmetyczna();
    for (int i = 0; i < dane.size(); i++) {
        suma += (dane[i] - arytmetyczna)*(dane[i] - arytmetyczna);
    }
    if (dane.size() < 30) return 1 / (dane.size() - 1) * suma;
    else return 1.0*(1 / dane.size() * suma);
}

float Proba::odchylenie() {
    return sqrt(Proba::wariancja());
}

float Proba::kurtoza() {

}