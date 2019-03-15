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

double Proba::minimum() {
    float min = dane[0];
    for (int i = 1; i < dane.size(); i++) {
        if (dane[i] < min) min = dane[i];
    }
    return min;
}

double Proba::maksimum() {
    float max = dane[0];
    for (int i = 1; i < dane.size(); i++) {
        if (dane[i] > max) max = dane[i];
    }
    return max;
}

double Proba::rozstep() {
    return Proba::maksimum() - Proba::minimum();
}

double Proba::kwartyl_1() {
    double tmp, n;
    tmp = 1.0 * (dane.size() + 1) / 4;
    double ulamek = modf(tmp, &n);
    return dane[n - 1] + ulamek * (dane[n] - dane[n - 1]);
}

double Proba::kwartyl_3() {
    double tmp, n;
    tmp = 1.0 * (3 * dane.size() + 1) / 4;
    double ulamek = modf(tmp, &n);
    return dane[n - 1] + ulamek * (dane[n] - dane[n - 1]);
}

double Proba::mediana() {
    if (dane.size() % 2 == 0) {
        return 0.5 * (dane[(dane.size() + 1) / 2] + dane[dane.size() / 2]);
    }
    if (dane.size() % 2 == 1) {
        return dane[(dane.size() + 1) / 2];
    }
}

double Proba::harmoniczna() {
    double suma = 0;
    for (int i = 0; i < dane.size(); i++) {
        suma += 1 / dane[i];
    }
    return dane.size() / suma;
}

double Proba::geometryczna() {
    float srednia = 1;
    for (int i = 0; i < dane.size(); i++) {
        srednia *= dane[i];
    }
    return pow(srednia, (1.0 / dane.size()));
}

double Proba::arytmetyczna() {
    float srednia = 0;
    for (int i = 0; i < dane.size(); i++) {
        srednia += dane[i];
    }
    return srednia / dane.size();
}

double Proba::potegowa_2() {
    float suma = 0, tmp = 0;
    for (int i = 0; i < dane.size(); i++) {
        suma += dane[i] * dane[i];
    }
    tmp = suma / dane.size();
    return pow(tmp, 1.0 / 2);
}

double Proba::potegowa_3() {
    float suma = 0, tmp = 0;
    for (int i = 0; i < dane.size(); i++) {
        suma += dane[i] * dane[i] * dane[i];
    }
    tmp = suma / dane.size();
    return pow(tmp, 1.0 / 3);
}

double Proba::wariancja() {
    double suma = 0, arytmetyczna = Proba::arytmetyczna();
    for (int i = 0; i < dane.size(); i++) {
        suma += (dane[i] - arytmetyczna) * (dane[i] - arytmetyczna);
    }
    if (dane.size() < 30) return 1.0 / (dane.size() - 1) * suma;
    else return (1.0 / dane.size() * suma);
}

double Proba::odchylenie() {
    return sqrt(Proba::wariancja());
}

double Proba::kurtoza() {
    int n = dane.size();
    double tmp = 0, suma = 0;
    double tmp1 = (n * (n + 1)) / ((n - 1) * (n - 2) * (n - 3));
    double tmp2 = (3 * (n - 1) * (n - 1)) / ((n - 2) * (n - 3));
    for (int i = 0; i < dane.size(); i++) {
        tmp = (dane[i] - Proba::arytmetyczna()) / Proba::odchylenie();
        suma += tmp * tmp * tmp * tmp;
    }
    return tmp1 * suma - tmp2;
}