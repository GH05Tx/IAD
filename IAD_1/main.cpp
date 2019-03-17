#include <iostream>
#include <memory>
#include "include/Proba.h"
#include "include/Dane.h"
#include "include/DaneIV.h"
#include "include/DaneIVC.h"
#include "include/DaneIS.h"
#include <iostream>
#include "gnuplot_i.hpp"
#include "include/DaneALL.h"

using namespace std;

int main() {
    Dane_ptr virginica(new DaneIV());
    Dane_ptr versi(new DaneIVC());
    Dane_ptr setosa(new DaneIS());
    Dane_ptr all(new DaneALL());
    virginica->wczytaj();
    versi->wczytaj();
    setosa->wczytaj();
    all->wczytaj();

    vector<float> dane=all->getPL();
    Proba_ptr proba13(new Proba(dane));
    cout << "\t" << "WSZYSTKIE GATUNKI" << endl;
    cout << "---- petal length ----" << endl;
    proba13->analizuj();
    dane=all->getPW();
    Proba_ptr proba14(new Proba(dane));
    cout << "---- petal width ----" << endl;
    proba14->analizuj();
    dane=all->getSL();
    Proba_ptr proba15(new Proba(dane));
    cout << "---- sepal length ----" << endl;
    proba15->analizuj();
    dane=all->getSW();
    Proba_ptr proba16(new Proba(dane));
    cout << "---- sepal width ----" << endl;
    proba16->analizuj();
    cout << endl;
    dane=virginica->getPL();
    Proba_ptr proba1(new Proba(dane));
    cout << "\t" << "IRIS-VIRGINICA" << endl;
    cout << "---- petal length ----" << endl;
    proba1->analizuj();
    dane=virginica->getPW();
    Proba_ptr proba2(new Proba(dane));
    cout << "---- petal width ----" << endl;
    proba2->analizuj();
    dane=virginica->getSL();
    Proba_ptr proba3(new Proba(dane));
    cout << "---- sepal length ----" << endl;
    proba3->analizuj();
    dane=virginica->getSW();
    Proba_ptr proba4(new Proba(dane));
    cout << "---- sepal width ----" << endl;
    proba4->analizuj();
    cout << endl;
    dane=versi->getPL();
    Proba_ptr proba5(new Proba(dane));
    cout << "\t" << "IRIS-VERSICOLOR" << endl;
    cout << "---- petal length ----" << endl;
    proba5->analizuj();
    dane=versi->getPW();
    Proba_ptr proba6(new Proba(dane));
    cout << "---- petal width ----" << endl;
    proba6->analizuj();
    dane=versi->getSL();
    Proba_ptr proba7(new Proba(dane));
    cout << "---- sepal length ----" << endl;
    proba7->analizuj();
    dane=versi->getSW();
    Proba_ptr proba8(new Proba(dane));
    cout << "---- sepal width ----" << endl;
    proba8->analizuj();
    cout << endl;
    dane=setosa->getPL();
    Proba_ptr proba9(new Proba(dane));
    cout << "\t" << "IRIS-SETOSA" << endl;
    cout << "---- petal length ----" << endl;
    proba9->analizuj();
    dane=setosa->getPW();
    Proba_ptr proba10(new Proba(dane));
    cout << "---- petal width ----" << endl;
    proba10->analizuj();
    dane=setosa->getSL();
    Proba_ptr proba11(new Proba(dane));
    cout << "---- sepal length ----" << endl;
    proba11->analizuj();
    dane=setosa->getSW();
    Proba_ptr proba12(new Proba(dane));
    cout << "---- sepal width ----" << endl;
    proba12->analizuj();

//Rysowanie wykresow

    Gnuplot wykres;
    wykres.set_xlabel("Sepal Length");
    wykres.set_ylabel("Sepal Width");
    wykres.set_xrange(4, 8);
    wykres.set_yrange(2, 5);
    wykres.set_grid();
    wykres.set_style("points");
    wykres.set_pointsize(1.5);
    wykres.plot_xy(versi->getSL(),versi->getSW(), "Sepal versicolor");
    wykres.plot_xy(virginica->getSL(),virginica->getSW(), "Sepal virginica");
    wykres.plot_xy(setosa->getSL(),setosa->getSW(), "Sepal setosa");
    Gnuplot wykres2;
    wykres2.set_xlabel("Petal Length");
    wykres2.set_ylabel("Petal Width");
    wykres2.set_xrange(0.9,8);
    wykres2.set_yrange(0,3);
    wykres2.set_grid();
    wykres2.set_style("points");
    wykres2.set_pointsize(1.5);
    wykres2.plot_xy(versi->getPL(),versi->getPW(), "Petal versicolor");
    wykres2.plot_xy(virginica->getPL(),virginica->getPW(), "Petal virginica");
    wykres2.plot_xy(setosa->getPL(),setosa->getPW(), "Petal setosa");
    cin.sync();
    cin.get();

    return 0;
}