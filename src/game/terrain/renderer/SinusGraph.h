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
    virtual double heightFunction(float valueX);
    virtual double heightFunctionDerivation(float valueX);
    virtual double depthFunction(float valueZ);
    virtual double depthFunctionDerivation(float valueZ);
};


#endif //COMPUTERGRAFIK_PRAKTIKUM_SINUSGRAPH_H
