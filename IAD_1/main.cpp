#include <iostream>
#include <memory>
#include "include/Proba.h"
#include "include/Dane.h"
#include "include/DaneIV.h"
#include "include/DaneIVC.h"
#include "include/DaneIS.h"
#include <iostream>
using namespace std;

int main() {
    Dane_ptr virginica(new DaneIV());
    Dane_ptr versi(new DaneIVC());
    Dane_ptr setosa(new DaneIS());
    virginica->wczytaj();
    versi->wczytaj();
    setosa->wczytaj();
    cout << "VIRGINICA SW: ";
    virginica->printPL();
    /*cout << endl << "-----------" << endl;
    cout << "VERSI PL: ";
    versi->printPL();
    cout << endl << "-----------" << endl;
    cout << "SETOSA PW: ";
    setosa->printPW();*/
    cout << endl << "-----------" << endl;
    vector<float> tmp = virginica->getPL();
    Proba_ptr proba1(new Proba(tmp));
    cout << "PROBA - VIRGINICA" << endl;
    proba1->wyswietl();
    cout << endl;
    cout << "- minimum: " << proba1->minimum() << endl;
    cout << "- maksimum: " << proba1->maksimum() << endl;
    cout << "- rozstep: " << proba1->rozstep() << endl;
    cout << "- kwartyl 1: " << proba1->kwartyl_1() << endl;
    cout << "- kwartyl 3: " << proba1->kwartyl_3() << endl;
    cout << "- mediana: " << proba1->mediana() << endl;
    cout << "- arytmetyczna: " << proba1->arytmetyczna() << endl;
    cout << "- harmoniczna: " << proba1->harmoniczna() << endl;
    cout << "- geometryczna: " << proba1->geometryczna() << endl;
    cout << "- potegowa 2: " << proba1->potegowa_2() << endl;
    cout << "- potegowa 3: " << proba1->potegowa_3() << endl;
    cout << "- wariancja: " << proba1->wariancja() << endl;
    cout << "- odchylenie: " << proba1->odchylenie() << endl;
    cout << "- kurtoza: " << proba1->kurtoza() << endl;

    return 0;
}