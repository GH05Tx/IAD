//
// Created by Jasiek on 26.03.2019.
//

#ifndef ZAD_2_KSREDNICH_H
#define ZAD_2_KSREDNICH_H

#include <vector>
#include "Klaster.h"
#include "Punkt.h"

class KSrednich {
private:
    vector<Klaster_ptr> klastry;
    vector<Pkt_ptr> wszystkiePunkty;
public:
    KSrednich(vector<Klaster_ptr>, vector<Pkt_ptr>);

    void ksrednich();

    Pkt_ptr getPunkt(int);

    double euklides(Pkt_ptr, Pkt_ptr);

    Pkt_ptr liczCentroid(int index);

    void ustawCentroidStart();

    void printPkts();

    void printKlaster(int);

    vector<Pkt_ptr> getKlaster(int);

    vector<double> getKlasterX(int, int);

    vector<double> getKlasterY(int, int);

    vector<double> getCentroX(int, int);

    vector<double> getCentroY(int, int);

    vector<double> getX(int);

    vector<double> getY(int);
};

typedef shared_ptr<KSrednich> KS_ptr;

#endif //ZAD_2_KSREDNICH_H
