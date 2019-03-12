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
    virginica->printSW();
    cout << endl << "-----------" << endl;
    cout << "VERSI PL: ";
    versi->printPL();
    cout << endl << "-----------" << endl;
    cout << "SETOSA PW: ";
    setosa->printPW();
    cout << endl << "-----------" << endl;
    vector<float> tmp = virginica->getPL();
    Proba_ptr proba1(new Proba(tmp));
    cout << proba1->arytmetyczna();

    return 0;
}