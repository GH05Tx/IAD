//
// Created by Jasiek on 30.03.2019.
//

#include "../include/Irys.h"
#include <fstream>
#include <cstring>
#include <iostream>

void Irys::wczytaj() {
    fstream plik;
    plik.open("../dane/irys.txt", ios::in);
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

        vector<double> values;
        values.push_back(sl);
        values.push_back(sw);
        values.push_back(pl);
        values.push_back(pw);

        Pkt_ptr point(new Punkt(values, 5));
        if (sl > 0 and sl < 10) {
            punkty.push_back(point);
        }
    }
    plik.close();
}

vector<Pkt_ptr> Irys::getPunkty() {
    return punkty;
}

void Irys::printAll() {
    for(int i=0; i<punkty.size(); i++)
    {
        punkty[i]->printPunkt();
        cout << punkty[i]->getKlaster() << endl;
    }
}