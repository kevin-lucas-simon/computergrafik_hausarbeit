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
    return 3 * x * x - 2 * x * x * x;
}

// f(x)
float PerlinGraph::fFunction(float x, int n) {
    float hash = hash_seed(seed + n);
    float angle = hash/std::numeric_limits<unsigned int>::max();
    return angle * (x - n);
}

// Gibt die Höhe von der X Position an, ermittelt aus der Funktion f(x)
float PerlinGraph::heightFunction(float valueX) {
    valueX = valueX / 8;

    float n = (int) valueX;
    if(valueX < 0) n--;

    float left = fFunction(valueX, n);
    float right = fFunction(valueX, n + 1);

    return 8 * lerp(left, right, smoothstep(valueX - n));
}

// Gibt die Steigung von der X Position an, ermittelt aus der Funktion f'(x)
float PerlinGraph::heightFunctionDerivation(float valueX) {
    float epsilon = 0.001;
    return (heightFunction(valueX + epsilon) - heightFunction(valueX - epsilon)) / (2 * epsilon);
}

// Gibt die Höhe von der Z Position an, ermittelt aus der Funktion g(x)
float PerlinGraph::depthFunction(float valueZ) {
    return -0.5 * valueZ * valueZ;
}

// Gibt die Steigung von der Z Position an, ermittelt aus der Funktion g'(x)
float PerlinGraph::depthFunctionDerivation(float valueZ) {
    return -1 * valueZ;
}