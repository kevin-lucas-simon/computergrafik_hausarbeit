//
// Created by kevin on 14.02.2022.
//

#include <cmath>
#include "FlatGraph.h"

FlatGraph::FlatGraph() {}

FlatGraph::~FlatGraph() {}

// Gibt die Höhe von der X Position an, ermittelt aus der Funktion f(x)
double FlatGraph::heightFunction(float valueX) {
    return 0;
}

// Gibt die Steigung von der X Position an, ermittelt aus der Funktion f'(x)
double FlatGraph::heightFunctionDerivation(float valueX) {
    return 0;
}

// Gibt die Höhe von der Z Position an, ermittelt aus der Funktion g(x)
double FlatGraph::depthFunction(float valueZ) {
    return -0.5 * valueZ * valueZ;
}

// Gibt die Steigung von der Z Position an, ermittelt aus der Funktion g'(x)
double FlatGraph::depthFunctionDerivation(float valueZ) {
    return -1 * valueZ;
}