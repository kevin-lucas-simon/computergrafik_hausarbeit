//
// Created by kevin on 16.02.2022.
//

#include <memory>
#include <iostream>
#include "PerlinGraph.h"
#include <random>


// Konstruktor mit bestimmten Seed
PerlinGraph::PerlinGraph() {
    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_int_distribution<int> distr(0, RAND_MAX);
    this->seed = distr(eng);
    std::cout << "Used Seed: " << this->seed << std::endl;
}

// Destruktor
PerlinGraph::~PerlinGraph() = default;

// Lineare Interpolation
double PerlinGraph::lerp(float left, float right, float valueX) {
    return left * (1 - valueX) + right * valueX;
}

// Kubische Interpolation
double PerlinGraph::smoothstep(float x) {
    return 3 * pow(x, 2) - 2 * pow(x, 3);
}

// Erzeugt eine zufällige Tangente an einem Punkt n
double PerlinGraph::tangent(float x, int n) {
    // Sonderfall bei x=0 für eine besser aussehende Start-Location (keine Steigung)
    if(n == 0)  return 0;

    // Zufälligen Wert aus dem Hash generieren
    float hash = hash_seed(seed + n);
    //std::cout << "Hash --> " << hash;
    float angle = hash/std::numeric_limits<unsigned int>::max();
    return angle * (x - n);
}

// Rekursive Oktave-Funktion des Perlin-Noise-Verfahrens, Variable octave definiert die Anzahl der Durchführungen
double PerlinGraph::perlinNoise(float valueX, unsigned int octave) {
    // Ende der Rekursion
    if(octave <= 0) return 0;

    // Koordinaten auf Dichte der Oktave anpassen
    float x = valueX / octave / MIN_OCTAVE_WIDTH;

    // Ganzzahlige Koordinate für Interpolation ermitteln
    float n = (int) x;
    if(x < 0) n--;

    // Steigung Links und Rechts anhand des Seeds erzeugen
    float left = tangent(x, n);
    float right = tangent(x, n + 1);

    // Interpolieren und zur nächstkleineren Oktave addieren
    return perlinNoise(valueX, octave - 1)
           + octave * MIN_OCTAVE_HEIGHT * lerp(left, right, smoothstep(x - n));
}

// Gibt die Höhe von der X Position an, ermittelt aus der Funktion f(x)
double PerlinGraph::heightFunction(float valueX) {
    // Ermittlung des Schwierigkeitsfaktors
    float difficultyFactor = (valueX - DIFFICULTY_INTERVAL) * DIFFICULTY_FACTOR / DIFFICULTY_INTERVAL + 1;
    if(valueX < DIFFICULTY_INTERVAL) difficultyFactor = 1;

    // Rekursiver Aufruf des Perlin-Noise-Verfahrens
    return perlinNoise(valueX, OCTAVE_COUNT) * difficultyFactor;
}

// Gibt die Steigung von der X Position an, ermittelt aus der Funktion f'(x)
double PerlinGraph::heightFunctionDerivation(float valueX) {
    return (heightFunction(valueX + EPSILON) - heightFunction(valueX - EPSILON)) / (2 * EPSILON);
}

// Gibt die Höhe von der Z Position an, ermittelt aus der Funktion g(x)
double PerlinGraph::depthFunction(float valueZ) {
    return -0.5 * valueZ * valueZ;
}

// Gibt die Steigung von der Z Position an, ermittelt aus der Funktion g'(x)
double PerlinGraph::depthFunctionDerivation(float valueZ) {
    return -1 * valueZ;
}