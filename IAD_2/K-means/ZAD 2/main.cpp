#include <iostream>
#include <cstdlib>
#include <ctime>
#include "include/Irys.h"
#include "include/Klaster.h"
#include "include/KSrednich.h"
#include "include/Punkt.h"
#include <memory>
#include "gnuplot_i.hpp"
#include "include/Wino.h"
#include "include/Abalone.h"
#include <unistd.h>

int main() {

    srand(time(NULL));
    Gnuplot gnuplot;
    gnuplot.set_grid();
    gnuplot.set_style("points");
    gnuplot.set_pointsize(2);

    //////BADANIE 1 - POCZĄTEK//////
    gnuplot.set_xrange(0, 7);
    gnuplot.set_yrange(0, 7);
    Ir_ptr irys(new Irys());
    irys->wczytaj();
    vector<Pkt_ptr> pkt_irys = irys->getPunkty();
    Klaster_ptr klaster1(new Klaster());
    Klaster_ptr klaster2(new Klaster());
    Klaster_ptr klaster3(new Klaster());
    vector<Klaster_ptr> klastry;
    klastry.push_back(klaster1);
    klastry.push_back(klaster2);
    klastry.push_back(klaster3);
    KS_ptr metoda(new KSrednich(klastry, pkt_irys));
    metoda->ustawCentroidStart();

    int sleeping = 2;
    int max = 15;

    vector<double> X = metoda->getX(2);
    vector<double> Y = metoda->getY(3);
    gnuplot.plot_xy(X, Y, "wszystkie punkty");
    sleep(sleeping);
    vector<double> xc1 = metoda->getCentroX(0, 2);
    vector<double> xc2 = metoda->getCentroX(1, 2);
    vector<double> xc3 = metoda->getCentroX(2, 2);
    vector<double> yc1 = metoda->getCentroY(0, 3);
    vector<double> yc2 = metoda->getCentroY(1, 3);
    vector<double> yc3 = metoda->getCentroY(2, 3);
    gnuplot.plot_xy(xc1, yc1, "Centroid 1");
    gnuplot.plot_xy(xc2, yc2, "Centroid 2");
    gnuplot.plot_xy(xc3, yc3, "Centroid 3");
    sleep(sleeping);
    X.clear();
    Y.clear();
    gnuplot.remove_tmpfiles();
    gnuplot.reset_plot();

    for (int i = 0; i < max; i++) {
        metoda->ksrednich();
        vector<double> x1 = metoda->getKlasterX(0, 2);
        vector<double> x2 = metoda->getKlasterX(1, 2);
        vector<double> x3 = metoda->getKlasterX(2, 2);
        vector<double> y1 = metoda->getKlasterY(0, 3);
        vector<double> y2 = metoda->getKlasterY(1, 3);
        vector<double> y3 = metoda->getKlasterY(2, 3);
        vector<double> xc1 = metoda->getCentroX(0, 2);
        vector<double> xc2 = metoda->getCentroX(1, 2);
        vector<double> xc3 = metoda->getCentroX(2, 2);
        vector<double> yc1 = metoda->getCentroY(0, 3);
        vector<double> yc2 = metoda->getCentroY(1, 3);
        vector<double> yc3 = metoda->getCentroY(2, 3);
        gnuplot.plot_xy(x1, y1, "Klaster 1");
        gnuplot.plot_xy(x2, y2, "Klaster 2");
        gnuplot.plot_xy(x3, y3, "Klaster 3");
        gnuplot.plot_xy(xc1, yc1, "Centroid 1");
        gnuplot.plot_xy(xc2, yc2, "Centroid 2");
        gnuplot.plot_xy(xc3, yc3, "Centroid 3");
        sleep(sleeping);
        x1.clear();
        y1.clear();
        x2.clear();
        y2.clear();
        x3.clear();
        y3.clear();
        xc1.clear();
        yc1.clear();
        xc2.clear();
        yc2.clear();
        xc3.clear();
        yc3.clear();
        gnuplot.remove_tmpfiles();
        gnuplot.reset_plot();
    }
    cin.sync();
    cin.get();
    //////BADANIE 1 - KONIEC//////

/*
    //////BADANIE 2 - POCZĄTEK//////
    gnuplot.set_xrange(0, 7);
    gnuplot.set_yrange(0, 7);
    Wino_ptr winko(new Wino());
    winko->wczytaj();
    vector<Pkt_ptr> pkt_wino = winko->getPunkty();
    Klaster_ptr klaster1(new Klaster());
    Klaster_ptr klaster2(new Klaster());
    vector<Klaster_ptr> klastry;
    klastry.push_back(klaster1);
    klastry.push_back(klaster2);
    KS_ptr metoda(new KSrednich(klastry, pkt_wino));
    metoda->ustawCentroidStart();

    int sleeping = 1; //czas pomiędzy generowaniem wykresów (w sekundach)
    int max = 50;//liczba iteracji które ma wykonać program

    vector<double> X = metoda->getX(12);
    vector<double> Y = metoda->getY(6);
    gnuplot.plot_xy(X, Y, "wszystkie punkty");
    sleep(sleeping);
    vector<double> xc1 = metoda->getCentroX(0,12);
    vector<double> xc2 = metoda->getCentroX(1,12);
    vector<double> yc1 = metoda->getCentroY(0,6);
    vector<double> yc2 = metoda->getCentroY(1,6);
    gnuplot.plot_xy(xc1, yc1, "Centroid 1");
    gnuplot.plot_xy(xc2, yc2, "Centroid 2");
    sleep(sleeping);
    X.clear();
    Y.clear();
    gnuplot.remove_tmpfiles();
    gnuplot.reset_plot();

    for (int i = 0; i < max; i++) {
        metoda->ksrednich();
        vector<double> x1 = metoda->getKlasterX(0,12);
        vector<double> x2 = metoda->getKlasterX(1,12);
        vector<double> y1 = metoda->getKlasterY(0,6);
        vector<double> y2 = metoda->getKlasterY(1,6);
        vector<double> xc1 = metoda->getCentroX(0,12);
        vector<double> xc2 = metoda->getCentroX(1,12);
        vector<double> yc1 = metoda->getCentroY(0,6);
        vector<double> yc2 = metoda->getCentroY(1,6);
        gnuplot.plot_xy(x1, y1, "Klaster 1");
        gnuplot.plot_xy(x2, y2, "Klaster 2");
        gnuplot.plot_xy(xc1, yc1, "Centroid 1");
        gnuplot.plot_xy(xc2, yc2, "Centroid 2");
        sleep(sleeping);
        x1.clear();
        y1.clear();
        x2.clear();
        y2.clear();
        xc1.clear();
        yc1.clear();
        xc2.clear();
        yc2.clear();
        gnuplot.remove_tmpfiles();
        gnuplot.reset_plot();
    }
    cin.sync();
    cin.get();
    //////BADANIE 2 - KONIEC//////
*/
/*
    //////BADANIE 3 - POCZĄTEK//////
    gnuplot.set_xrange(0, 0.8);
    gnuplot.set_yrange(-0.1, 1.2);
    Abalone_ptr abalo(new Abalone());
    abalo->wczytaj();
    vector<Pkt_ptr> pkt_abalo = abalo->getPunkty();
    Klaster_ptr klaster1(new Klaster());
    Klaster_ptr klaster2(new Klaster());
    Klaster_ptr klaster3(new Klaster());
    Klaster_ptr klaster4(new Klaster());
    vector<Klaster_ptr> klastry;
    klastry.push_back(klaster1);
    klastry.push_back(klaster2);
    klastry.push_back(klaster3);
    klastry.push_back(klaster4);
    KS_ptr metoda(new KSrednich(klastry, pkt_abalo));
    metoda->ustawCentroidStart();

    int sleeping = 10; //czas pomiędzy generowaniem wykresów (w sekundach)
    int max = 50;//liczba iteracji które ma wykonać program

    vector<double> X = metoda->getX(5);
    vector<double> Y = metoda->getY(0);
    gnuplot.plot_xy(X, Y, "wszystkie punkty");
    sleep(sleeping);
    vector<double> xc1 = metoda->getCentroX(0, 5);
    vector<double> xc2 = metoda->getCentroX(1, 5);
    vector<double> xc3 = metoda->getCentroX(2, 5);
    vector<double> xc4 = metoda->getCentroX(3, 5);

    vector<double> yc1 = metoda->getCentroY(0, 0);
    vector<double> yc2 = metoda->getCentroY(1, 0);
    vector<double> yc3 = metoda->getCentroY(2, 0);
    vector<double> yc4 = metoda->getCentroY(3, 0);

    gnuplot.plot_xy(xc1, yc1, "Centroid 1");
    gnuplot.plot_xy(xc2, yc2, "Centroid 2");
    gnuplot.plot_xy(xc3, yc3, "Centroid 3");
    gnuplot.plot_xy(xc4, yc4, "Centroid 4");

    sleep(sleeping);
    X.clear();
    Y.clear();
    gnuplot.remove_tmpfiles();
    gnuplot.reset_plot();
    for (int j = 0; j < 20; j++) {

        for (int i = 0; i < 10; i++) {
            metoda->ksrednich();
        }
        vector<double> x1 = metoda->getKlasterX(0, 5);
        vector<double> x2 = metoda->getKlasterX(1, 5);
        vector<double> x3 = metoda->getKlasterX(2, 5);
        vector<double> x4 = metoda->getKlasterX(3, 5);
        vector<double> y1 = metoda->getKlasterY(0, 0);
        vector<double> y2 = metoda->getKlasterY(1, 0);
        vector<double> y3 = metoda->getKlasterY(2, 0);
        vector<double> y4 = metoda->getKlasterY(3, 0);

        vector<double> xc1 = metoda->getCentroX(0, 5);
        vector<double> xc2 = metoda->getCentroX(1, 5);
        vector<double> xc3 = metoda->getCentroX(2, 5);
        vector<double> xc4 = metoda->getCentroX(3, 5);

        vector<double> yc1 = metoda->getCentroY(0, 0);
        vector<double> yc2 = metoda->getCentroY(1, 0);
        vector<double> yc3 = metoda->getCentroY(2, 0);
        vector<double> yc4 = metoda->getCentroY(3, 0);
        gnuplot.plot_xy(x1, y1, "Klaster 1");
        gnuplot.plot_xy(x2, y2, "Klaster 2");
        gnuplot.plot_xy(x3, y3, "Klaster 3");
        gnuplot.plot_xy(x4, y4, "Klaster 4");
        gnuplot.plot_xy(xc1, yc1, "Centroid 1");
        gnuplot.plot_xy(xc2, yc2, "Centroid 2");
        gnuplot.plot_xy(xc3, yc3, "Centroid 3");
        gnuplot.plot_xy(xc4, yc4, "Centroid 4");

        sleep(sleeping);
        x1.clear();
        y1.clear();
        x2.clear();
        y2.clear();
        x3.clear();
        y3.clear();
        x4.clear();
        y4.clear();
        xc1.clear();
        yc1.clear();
        xc2.clear();
        yc2.clear();
        xc3.clear();
        yc3.clear();
        xc4.clear();
        yc4.clear();
        gnuplot.remove_tmpfiles();
        gnuplot.reset_plot();
    }
    cin.sync();
    cin.get();
    //////BADANIE 3 - KONIEC//////
*/
    return 0;
}