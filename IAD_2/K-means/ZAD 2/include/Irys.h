//
// Created by Jasiek on 30.03.2019.
//

#ifndef ZAD_2_IRYS_H
#define ZAD_2_IRYS_H

#include "Punkt.h"
#include <memory>

using namespace std;

class Irys {
private:
    vector<Pkt_ptr> punkty;
public:
    Irys() = default;

    void wczytaj();

    vector<Pkt_ptr> getPunkty();

    void printAll();
};
typedef shared_ptr<Irys> Ir_ptr;

#endif //ZAD_2_IRYS_H
