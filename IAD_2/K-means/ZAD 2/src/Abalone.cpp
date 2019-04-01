//
// Created by Jasiek on 31.03.2019.
//

#include "../include/Abalone.h"
#include <fstream>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include "string"
#include <algorithm>
#include <sstream>

void Abalone::wczytaj() {
    vector<vector<double>> dzialaj;
    vector<double> pls;
    ifstream plik;
    vector<string> pomik;
    plik.open("../dane/abalone.txt", ios::in);
    if (!plik.good()) {
        cout << "ERROR - blad odczytu pliku" << endl;
        exit(0);
    }
    string tmp;
    while (!plik.eof()) {
        getline(plik, tmp);
        string tmp2;
        stringstream ss(tmp);
        while (getline(ss, tmp2, ',')) {
            pomik.push_back(tmp2);
        }
    }
    int wymiar = 8;
    int z = 0;
    for (int j = 1; j < 4177; j++) {
        vector <double> values;
        for (int i = 0; i < wymiar; i++) {
            values.push_back(stod(pomik[z]));
            z++;
        }
        Pkt_ptr point(new Punkt(values, 5));
        punkty.push_back(point);
    }
}

vector<Pkt_ptr> Abalone::getPunkty() {
    return punkty;
}

void Abalone::printAll() {
    for(int i=0; i<punkty.size(); i++)
    {
        punkty[i]->printPunkt();
        //cout << punkty[i]->getKlaster() << endl;
    }
}