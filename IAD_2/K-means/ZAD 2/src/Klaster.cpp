//
// Created by Jasiek on 26.03.2019.
//

#include "../include/Klaster.h"
#include <vector>

void Klaster::setCentroid(Pkt_ptr centr) {
    this->centroid = centr;
}

Pkt_ptr Klaster::getCentroid() {
    return centroid;
}

void Klaster::printCentroid() {
    centroid->printPunkt();
}
