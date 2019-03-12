//
// Created by Jasiek on 11.03.2019.
//

#include "../include/Dane.h"
#include <fstream>
#include <string>
#include <cstring>
#include <stdio.h>
#include <vector>
#include <stdlib.h>
#include <math.h>

/*
void Dane::wczytaj() {
    fstream plik;
    plik.open("../irys_IAD.txt", ios::in);
    if (!plik.good()) {
        cout << "ERROR - blad odczytu pliku" << endl;
        exit(0);
    }
    string tmp;
    while (!plik.eof()) {
        getline(plik, tmp);
        char cstr[tmp.size() + 1];
        char sL[3];
        char sW[3];
        char pL[3];
        char pW[3];
        double sl, sw, pl, pw;
        strcpy(cstr, tmp.c_str());
        for (int i = 0; i < 3; i++) {
            sL[i] = cstr[i];
            sW[i] = cstr[i + 4];
            pL[i] = cstr[i + 8];
            pW[i] = cstr[i + 12];
        }
        sl = atof(sL);
        sw = atof(sW);
        pl = atof(pL);
        pw = atof(pW);
        if (sl > 0 and sl < 10) {
            sepalLength.push_back(sl);
            sepalWidth.push_back(sw);
            petalLength.push_back(pl);
            petalWidth.push_back(pw);
            //cout << sl << " " << sw << " " << pl << " " << pw << endl;
        }
        string gatunek("");
        for (int i = 16; i < strlen(cstr); i++) {
            gatunek += cstr[i];
        }
    }
    plik.close();
}
*/
void Dane::printSL() {
    for (int i = 0; i < sepalLength.size(); i++) {
        cout << sepalLength[i] << " ";
    }
}

void Dane::printSW() {
    for (int i = 0; i < sepalWidth.size(); i++) {
        cout << sepalWidth[i] << " ";
    }
}

void Dane::printPL() {
    for (int i = 0; i < petalLength.size(); i++) {
        cout << petalLength[i] << " ";
    }
}

void Dane::printPW() {
    for (int i = 0; i < petalWidth.size(); i++) {
        cout << petalWidth[i] << " ";
    }
}

vector<float> Dane::getSL() {
    return sepalLength;
}

vector<float> Dane::getSW() {
    return sepalWidth;
}

vector<float> Dane::getPL() {
    return petalLength;
}

vector<float> Dane::getPW() {
    return petalWidth;
}