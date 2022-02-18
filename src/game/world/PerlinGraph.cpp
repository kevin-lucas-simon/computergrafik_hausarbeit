//
// Created by kevin on 16.02.2022.
//

#include <memory>
#include <iostream>
#include "PerlinGraph.h"

// Standardkonstruktor mit zufälligen Seed
PerlinGraph::PerlinGraph() { PerlinGraph(rand() % RAND_MAX); }

// Konstruktor mit bestimmten Seed
PerlinGraph::PerlinGraph(unsigned int seed) {
    this->seed = seed;
    std::cout << "Used Seed: " << this->seed << std::endl;
}

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

// Erzeugt eine zufällige Tangente an einem Punkt n
float PerlinGraph::fFunction(float x, int n) {
    // Sonderfall bei x=0 für eine besser aussehende Start-Location (keine Steigung
    if(n == 0)  return 0;

    // Zufälligen Wert aus dem Hash generieren
    float hash = hash_seed(seed + n);
    float angle = hash/std::numeric_limits<unsigned int>::max();
    return angle * (x - n);
}

// Rekursive Oktave-Funktion des Perlin-Noise-Verfahrens, Variable octave definiert die Anzahl der Durchführungen
float PerlinGraph::perlinOctave(float valueX, unsigned int octave) {
    // Ende der Rekursion
    if(octave <= 0) return 0;

    // Koordinaten auf Dichte der Oktave anpassen
    float x = valueX / octave / MIN_OCTAVE_WIDTH;

    // Ganzzahlige Koordinate für Interpolation ermitteln
    float n = (int) x;
    if(x < 0) n--;

    // Steigung Links und Rechts anhand des Seeds erzeugen
    float left = fFunction(x, n);
    float right = fFunction(x, n + 1);

    // Interpolieren und zur nächstkleineren Oktave addieren
    return perlinOctave(valueX, octave-1)
        + octave * MIN_OCTAVE_HEIGHT * lerp(left, right, smoothstep(x - n));
}

// Gibt die Höhe von der X Position an, ermittelt aus der Funktion f(x)
float PerlinGraph::heightFunction(float valueX) {
    float difficultyFactor = (valueX - DIFFICULTY_INTERVAL) * DIFFICULTY_FACTOR / DIFFICULTY_INTERVAL + 1;
    if(valueX < DIFFICULTY_INTERVAL) difficultyFactor = 1;
    return perlinOctave(valueX, OCTAVE_COUNT) * difficultyFactor;
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