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
    virtual float heightFunction(float valueX);
    virtual float heightFunctionDerivation(float valueX);
    virtual float depthFunction(float valueZ);
    virtual float depthFunctionDerivation(float valueZ);
};


#endif //COMPUTERGRAFIK_PRAKTIKUM_FLATGRAPH_H
