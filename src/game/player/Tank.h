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

    // Definition Physikalischer Konstanten
    const float GRAVITY_FORCE = 1.0;    // Positiver Wert, entspricht nicht der reale Konstante
    const float USER_FORCE = 1.0;       // Positiver Wert
    const float SLOPE_FORCE = 1.0;      // Positiver Wert
    const float DRAG_FACTOR = 0.99;     // Wert zwischen 0 (UHU Kleber) und 1 (Glatteis)
    const float LIFT_HEIGHT = 0.05;     // Positiver Wert
    const float STOPPING_SPEED = 0.003; // Positiver Wert
};

#endif /* Tank_hpp */
