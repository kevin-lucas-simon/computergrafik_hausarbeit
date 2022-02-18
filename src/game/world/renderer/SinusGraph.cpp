//
// Created by kevin on 10.02.2022.
//

#include "SinusGraph.h"

SinusGraph::SinusGraph() {}

SinusGraph::~SinusGraph() {}

// Gibt die Höhe von der X Position an, ermittelt aus der Funktion f(x)
double SinusGraph::heightFunction(float valueX) {
    return 0.025 * sin(valueX) * valueX;
}

// Gibt die Steigung von der X Position an, ermittelt aus der Funktion f'(x)
double SinusGraph::heightFunctionDerivation(float valueX) {
    return 0.025 * cos(valueX) * valueX + 0.025 * sin(valueX);
}

// Gibt die Höhe von der Z Position an, ermittelt aus der Funktion g(x)
double SinusGraph::depthFunction(float valueZ) {
    return -0.5 * valueZ * valueZ;
}

// Gibt die Steigung von der Z Position an, ermittelt aus der Funktion g'(x)
double SinusGraph::depthFunctionDerivation(float valueZ) {
    return -1 * valueZ;
}