//
// Created by kevin on 16.02.2022.
//

#include <memory>
#include <iostream>
#include "PerlinGraph.h"

// Standardkonstruktor mit zufälligen Seed
PerlinGraph::PerlinGraph() { PerlinGraph(rand() % RAND_MAX); }

// Konstruktor mit bestimmten Seed
PerlinGraph::PerlinGraph(unsigned int seed) { this->seed = seed; }

// Destruktor
PerlinGraph::~PerlinGraph() {}

// Lineare Interpolation
float PerlinGraph::lerp(float a, float b, float x) {
    return a * (1 - x) + b * x;
}

// Kubische Interpolation
float PerlinGraph::smoothstep(float x) {
    return x * x * (3 - 2 * x);
}

// Gibt die Höhe von der X Position an, ermittelt aus der Funktion f(x)
float PerlinGraph::heightFunction(float valueX) {
    float hash1 = hash_seed(seed + (int) valueX);
    float angleA = hash1/std::numeric_limits<unsigned int>::max();
    float hash2 = hash_seed(seed + (int) valueX + 1);
    float angleB = hash2/std::numeric_limits<unsigned int>::max();
    return lerp(angleA, angleB,smoothstep(valueX - (int) valueX));
}

// Gibt die Steigung von der X Position an, ermittelt aus der Funktion f'(x)
float PerlinGraph::heightFunctionDerivation(float valueX) {
    return 0;
}

// Gibt die Höhe von der Z Position an, ermittelt aus der Funktion g(x)
float PerlinGraph::depthFunction(float valueZ) {
    return -0.5 * valueZ * valueZ;
}

// Gibt die Steigung von der Z Position an, ermittelt aus der Funktion g'(x)
float PerlinGraph::depthFunctionDerivation(float valueZ) {
    return -1 * valueZ;
}