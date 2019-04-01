//
// Created by Jasiek on 26.03.2019.
//

#include "../include/KSrednich.h"
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <stdlib.h>
#include <random>

KSrednich::KSrednich(vector<Klaster_ptr> klas, vector<Pkt_ptr> pkt) {
    this->klastry = klas;
    this->wszystkiePunkty = pkt;
}

void KSrednich::ustawCentroidStart() {
    int zakres = wszystkiePunkty.size();
    for (int i = 0; i < klastry.size(); i++) {
        int index = rand() % zakres;
        klastry[i]->setCentroid(getPunkt(index));
        wszystkiePunkty[index]->setKlaster(i);
    }
}

Pkt_ptr KSrednich::liczCentroid(int index) {
    int size = wszystkiePunkty[0]->getValues().size();
    vector<double> wspol, wspol2(size, 0);
    int count = 0;
    for (int i = 0; i < wszystkiePunkty.size(); i++) {

        if (wszystkiePunkty[i]->getKlaster() == index) {
            count++;
            wspol = wszystkiePunkty[i]->getValues();

            for (int j = 0; j < wspol.size(); j++) {
                wspol2[j] += wspol[j];
            }
        }
    }
    for (int j = 0; j < wspol2.size(); j++) {
        if (count == 0) wspol2[j] = 1.0 * wspol2[j];
        else wspol2[j] = 1.0 * wspol2[j] / count;
    }
    Pkt_ptr point(new Punkt(wspol2, 5));
    return point;
}

double KSrednich::euklides(Pkt_ptr x, Pkt_ptr y) {
    vector<double> tmp = x->getValues(), tmp2 = y->getValues();
    double value = 0;
    for (int i = 0; i < x->getValues().size(); i++) {
        value += (tmp[i] - tmp2[i]) * (tmp[i] - tmp2[i]);
    }
    return sqrt(value);
}

void KSrednich::ksrednich() {

    for (int j = 0; j < wszystkiePunkty.size(); j++) {
        vector<double> min;

        for (int i = 0; i < klastry.size(); i++) {
            min.push_back(euklides(klastry[i]->getCentroid(), wszystkiePunkty[j]));
        }
        double mini = min[0];
        int index = 0;
        for (int k = 0; k < min.size(); k++) {
            if (min[k] < mini) {
                mini = min[k];
                index = k;
            }
        }
        wszystkiePunkty[j]->setKlaster(index);
    }
    for (int i = 0; i < klastry.size(); i++) {
        klastry[i]->setCentroid(liczCentroid(i));
    }
}

Pkt_ptr KSrednich::getPunkt(int i) {
    return wszystkiePunkty[i];
}

vector<double> KSrednich::getKlasterX(int index, int x) {
    vector<double> tmp, tmp2;
    for (int i = 0; i < wszystkiePunkty.size(); i++) {
        if (wszystkiePunkty[i]->getKlaster() == index) {
            tmp = wszystkiePunkty[i]->getValues();
            tmp2.push_back(tmp[x]);
        }
    }
    return tmp2;
}

vector<double> KSrednich::getKlasterY(int index, int y) {
    vector<double> tmp, tmp2;
    for (int i = 0; i < wszystkiePunkty.size(); i++) {
        if (wszystkiePunkty[i]->getKlaster() == index) {
            tmp = wszystkiePunkty[i]->getValues();
            tmp2.push_back(tmp[y]);
        }
    }
    return tmp2;
}

vector<double> KSrednich::getCentroX(int index, int x) {
    vector<double> tmp, final;
    tmp = (klastry[index]->getCentroid())->getValues();
    final.push_back(tmp[x]);
    return final;
}

vector<double> KSrednich::getCentroY(int index, int y) {
    vector<double> tmp, final;
    tmp = (klastry[index]->getCentroid())->getValues();
    final.push_back(tmp[y]);
    return final;
}

vector<double> KSrednich::getX(int x) {
    vector<double> tmp, final;
    for(int i=0; i<wszystkiePunkty.size(); i++)
    {
        tmp = wszystkiePunkty[i]->getValues();
        final.push_back(tmp[x]);
    }
    return final;
}

vector<double> KSrednich::getY(int y) {
    vector<double> tmp, final;
    for(int i=0; i<wszystkiePunkty.size(); i++)
    {
        tmp = wszystkiePunkty[i]->getValues();
        final.push_back(tmp[y]);
    }
    return final;
}

vector<Pkt_ptr> KSrednich::getKlaster(int index) {
    vector<Pkt_ptr> tmp;
    for (int i = 0; i < wszystkiePunkty.size(); i++) {
        if (wszystkiePunkty[i]->getKlaster() == index) {
            tmp.push_back(wszystkiePunkty[i]);
        }
    }
    return tmp;
}

void KSrednich::printPkts() {
    for (int i = 0; i < wszystkiePunkty.size(); i++) {
        wszystkiePunkty[i]->printPunkt();
    }
}

void KSrednich::printKlaster(int index) {
    for (int i = 0; i < wszystkiePunkty.size(); i++) {
        if (wszystkiePunkty[i]->getKlaster() == index) {
            wszystkiePunkty[i]->printPunkt();
        }
    }
}