//
// Created by Jasiek on 31.03.2019.
//

#ifndef ZAD_2_WINO_H
#define ZAD_2_WINO_H

#include <memory>
#include <vector>
#include <iostream>
#include "Punkt.h"

class Wino {
private:
    vector<Pkt_ptr> punkty;
public:
    Wino() = default;

    void wczytaj();

    vector<Pkt_ptr> getPunkty();

    void printAll();
};
typedef shared_ptr<Wino> Wino_ptr;


#endif //ZAD_2_WINO_H
