//
// Created by kevin on 11.02.2022.
//

#ifndef Tank_hpp
#define Tank_hpp

#include <stdio.h>
#include <game/world/TerrainControlService.h>
#include "model/Model.h"

class Tank : public BaseModel
{
public:
    Tank();
    virtual ~Tank();
    bool loadModels(const char* ChassisFile, const char* CannonFile);
    void bindToTerrain(TerrainControlService* terrainControl);
    void update(float dTime, int keyFrontBack);
    virtual void draw(const BaseCamera& Cam);
protected:
    void calculatePhysics(float dTime, int keyFrontBack);
    void calculateTransformation();

    Model* modelChassis;
    TerrainControlService* terrainControl;

    Vector position;
    Vector velocity;

    // Beschleunigungsrate des Nutzers beim Fahren, positiver Wert
    const float USER_FORCE_DRIVING = 2.0;
    // Beschleunigungsrate des Nutzers beim Fallen, positiver Wert
    const float USER_FORCE_FALLING = 1.0;
    // Gravitation, positiver Wert, entspricht nicht der reale Konstante
    const float GRAVITY_FORCE = 0.2;
    // Abbremsungs- und Beschleunigungsrate eines Gefälles beim Fahren, positiver Wert
    const float SLOPE_FORCE = 0.6;
    // Benötigte Höhe zum Abheben des Fahrzeugs, positiver Wert
    const float LIFT_HEIGHT = 0.01;
    // Rate der Abbremsung generell beim Fahren, Wert zwischen 0 (UHU Kleber) und 1 (Glatteis)
    const float GENERAL_DRAG = 0.99;
    // Rate der Abbremsung, wenn der Nutzer auf ein Berg knallt, Wert zwischen 0 (UHU Kleber) und 1 (Glatteis)
    const float IMPACT_DRAG = 0.4;
    // Minimalgeschwindigkeit, darunter hält das Fahrzeug an, positiver Wert
    const float STOPPING_SPEED = 0.003;
};

#endif /* Tank_hpp */
