//
// Created by Jasiek on 17.05.2019.
//

#ifndef IAD_MLP_SERVICE_H
#define IAD_MLP_SERVICE_H
#pragma once
#include "Net.h"

class Service {
protected:
    Net& network;

public:
	Service(Net& network) : network(network){	}
	virtual void Execute() = 0;
	virtual ~Service() {};
};


#endif //IAD_MLP_SERVICE_H
