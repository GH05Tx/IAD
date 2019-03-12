//
// Created by Jasiek on 12.03.2019.
//

#include <cstring>
#include "../include/DaneIS.h"
#include <fstream>


void DaneIS::wczytaj() {
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
        string gatunek("");
        for (int i = 16; i < strlen(cstr); i++) {
            gatunek += cstr[i];
        }
        if (gatunek == "Iris-setosa") {
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
            }
        }
    }
    plik.close();
}
