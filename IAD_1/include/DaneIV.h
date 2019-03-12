//
// Created by Jasiek on 12.03.2019.
//

#ifndef IAD_1_DANEIV_H
#define IAD_1_DANEIV_H
#include "Dane.h"
#include <memory>

class DaneIV: public Dane {
public:
    void wczytaj();
};
typedef shared_ptr<DaneIV> DIV_ptr;


#endif //IAD_1_DANEIV_H
