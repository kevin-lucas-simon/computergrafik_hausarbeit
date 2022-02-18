//
// Created by kevin on 10.02.2022.
//

#ifndef COMPUTERGRAFIK_PRAKTIKUM_GRAPHSERVICE_H
#define COMPUTERGRAFIK_PRAKTIKUM_GRAPHSERVICE_H


class GraphService
{
public:
    virtual ~GraphService() = 0 {};

    // Gibt die Höhe von der X Position an, ermittelt aus der Funktion f(x)
    virtual double heightFunction(float valueX) = 0;

    // Gibt die Steigung von der X Position an, ermittelt aus der Funktion f'(x)
    virtual double heightFunctionDerivation(float valueX) = 0;

    // Gibt die Höhe von der Z Position an, ermittelt aus der Funktion g(x)
    virtual double depthFunction(float valueZ) = 0;

    // Gibt die Steigung von der Z Position an, ermittelt aus der Funktion g'(x)
    virtual double depthFunctionDerivation(float valueZ) = 0;
};


#endif //COMPUTERGRAFIK_PRAKTIKUM_GRAPHSERVICE_H
