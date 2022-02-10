//
// Created by kevin on 10.02.2022.
//

#ifndef COMPUTERGRAFIK_PRAKTIKUM_SINUSGRAPH_H
#define COMPUTERGRAFIK_PRAKTIKUM_SINUSGRAPH_H


#include "GraphService.h"
#include "math.h"

class SinusGraph: virtual public GraphService
{
public:
    SinusGraph();
    virtual ~SinusGraph();

    // Implementation vom GraphService Interface
    virtual float heightFunction(float valueX);
    virtual float heightFunctionDerivation(float valueX);
    virtual float depthFunction(float valueZ);
    virtual float depthFunctionDerivation(float valueZ);
};


#endif //COMPUTERGRAFIK_PRAKTIKUM_SINUSGRAPH_H
