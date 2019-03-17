//
// Created by Jasiek on 12.03.2019.
//

#ifndef IAD_1_DANEIS_H
#define IAD_1_DANEIS_H


#include "Dane.h"
#include <memory>

class DaneIS: public Dane{
public:
    void wczytaj();
    DaneIS();
};
typedef shared_ptr<DaneIS> DIS_ptr;


#endif //IAD_1_DANEIS_H
