//
// Created by Jasiek on 12.03.2019.
//

#ifndef IAD_1_DANEIVC_H
#define IAD_1_DANEIVC_H
#include "Dane.h"
#include <memory>
class DaneIVC: public Dane {
public:
    void wczytaj();
    DaneIVC();
};
typedef shared_ptr<DaneIVC> DIVC_ptr;

#endif //IAD_1_DANEIVC_H
