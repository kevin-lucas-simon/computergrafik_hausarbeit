//
// Created by kevin on 11.02.2022.
//

#ifndef Tank_hpp
#define Tank_hpp

#include <stdio.h>
#include <game/terrain/TerrainControlService.h>
#include <framework/model/BaseModel.h>
#include <framework/model/Model.h>
#include "PlayerPositionService.h"

class Tank : public BaseModel, virtual public PlayerPositionService
{
public:
    Tank(char *assetDirectory, TerrainControlService* terrainControl);
    virtual ~Tank();
    void shader(BaseShader *shader, bool deleteOnDestruction) override;
    void update(float dTime, int keyForward, int keyBackward);
    virtual void draw(const BaseCamera& Cam);

    virtual float getHeight();
    virtual float getSpeed();
    virtual float getPosition();
protected:
    void calculatePhysics(float dTime, int keyForward, int keyBackward);
    void calculateTransformation();

    Model* modelChassis;
    Model* modelCannon;
    TerrainControlService* terrainControl;

    Vector position;
    Vector velocity;

    const char* chassisFile = "models/tank/tank_bottom.dae";
    const char* cannonFile = "models/tank/tank_top.dae";

    // Beschleunigungsrate des Nutzers beim Fahren, positiver Wert
    const float USER_FORCE_DRIVING = 0.65;
    // Beschleunigungsrate des Nutzers beim Fallen, positiver Wert
    const float USER_FORCE_FALLING = 0.9;
    // Entschleunigungsrate des Nutzers beim Fallen, Wert zwischen 0 (kein Effekt) und 1 (komplett gleiten)
    const float USER_FORCE_GLIDING = 0.17;

    // Gravitation, positiver Wert, entspricht nicht der reale Konstante
    const float GRAVITY_FORCE = 0.4;
    // Abbremsungs- und Beschleunigungsrate eines Gefälles beim Fahren, positiver Wert
    const float SLOPE_FORCE_UPWARD = 0.4;
    const float SLOPE_FORCE_DOWNWARD = 0.6;
    // Benötigte Höhe zum Abheben des Fahrzeugs, positiver Wert
    const float LIFT_HEIGHT = 0.02;

    // Rate der Abbremsung generell beim Fahren, Wert zwischen 0 (UHU Kleber) und 1 (Glatteis)
    const float GENERAL_DRAG = 0.99;
    // Rate der Abbremsung, wenn der Nutzer auf ein Berg knallt, Wert zwischen 0 (UHU Kleber) und 1 (Glatteis)
    const float IMPACT_DRAG = 0.05;

    // Minimalgeschwindigkeit, darunter hält das Fahrzeug an, positiver Wert
    const float MINIMUM_SPEED = 0.003;
    // Maximalgeschwindigkeit, positiver Wert (Empfehlenswert: Knapp kleiner als Chunkgröße)
    const float MAXIMUM_SPEED = 7.5;
};

#endif /* Tank_hpp */
