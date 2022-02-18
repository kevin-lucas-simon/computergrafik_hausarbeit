//
// Created by kevin on 16.02.2022.
//

#ifndef COMPUTERGRAFIK_PRAKTIKUM_PERLINGRAPH_H
#define COMPUTERGRAFIK_PRAKTIKUM_PERLINGRAPH_H


#include "GraphService.h"

// Orientiert sich grob an folgende Lösung: https://dens.website/articles/procedural-generation/perlin-noise
class PerlinGraph: virtual public GraphService {
public:
    PerlinGraph();
    PerlinGraph(unsigned int seed);
    virtual ~PerlinGraph();

    // Implementation vom GraphService Interface
    virtual double heightFunction(float valueX);
    virtual double heightFunctionDerivation(float valueX);
    virtual double depthFunction(float valueZ);
    virtual double depthFunctionDerivation(float valueZ);

protected:
    static double lerp(float left, float right, float valueX);
    static double smoothstep(float x);
    double tangent(float x, int n);
    double perlinNoise(float valueX, unsigned int octave);

    unsigned int seed;
    std::hash<unsigned int> hash_seed;

    // Anzahl und Größen der durchzuführenden Perlin-Noise Oktaven
    const unsigned int OCTAVE_COUNT = 10;
    const unsigned int MIN_OCTAVE_WIDTH = 6;
    const unsigned int MIN_OCTAVE_HEIGHT = 4;

    // Intervallbreite, in der die Schwierigkeit um den eingestellten Faktor sich erhöht (steilere Hänge usw.)
    const unsigned int DIFFICULTY_INTERVAL = 500;
    const double DIFFICULTY_FACTOR = 0.1;

    // Abstandsbreite zur Ermittlung der Ableitung
    const double EPSILON = 0.001;
};


#endif //COMPUTERGRAFIK_PRAKTIKUM_PERLINGRAPH_H
