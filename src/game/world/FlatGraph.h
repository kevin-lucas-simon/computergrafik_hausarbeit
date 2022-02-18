//
// Created by kevin on 14.02.2022.
//

#ifndef COMPUTERGRAFIK_PRAKTIKUM_FLATGRAPH_H
#define COMPUTERGRAFIK_PRAKTIKUM_FLATGRAPH_H


#include "GraphService.h"

class FlatGraph : virtual public GraphService {
public:
    FlatGraph();
    virtual ~FlatGraph();

    // Implementation vom GraphService Interface
    virtual double heightFunction(float valueX);
    virtual double heightFunctionDerivation(float valueX);
    virtual double depthFunction(float valueZ);
    virtual double depthFunctionDerivation(float valueZ);
};


#endif //COMPUTERGRAFIK_PRAKTIKUM_FLATGRAPH_H
