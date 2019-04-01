//
// Created by Jasiek on 31.03.2019.
//

#ifndef ZAD_2_ABALONE_H
#define ZAD_2_ABALONE_H
#include "Punkt.h"
#include <memory>

class Abalone {
private:
    vector<Pkt_ptr> punkty;
public:
    Abalone() = default;

    void wczytaj();

    vector<Pkt_ptr> getPunkty();

    void printAll();
};
typedef shared_ptr<Abalone> Abalone_ptr;


#endif //ZAD_2_ABALONE_H
