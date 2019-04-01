//
// Created by Jasiek on 26.03.2019.
//

#ifndef ZAD_2_CLUSTER_H
#define ZAD_2_CLUSTER_H

#include "Punkt.h"
#include <memory>
#include <vector>

class Klaster {
private:
    Pkt_ptr centroid;
public:
    Klaster() = default;

    void setCentroid(Pkt_ptr);

    Pkt_ptr getCentroid();

    void printCentroid();
};

typedef shared_ptr<Klaster> Klaster_ptr;

#endif //ZAD_2_CLUSTER_H
