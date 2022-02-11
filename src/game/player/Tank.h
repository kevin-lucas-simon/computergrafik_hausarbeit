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
    Model* modelChassis;
    TerrainControlService* terrainControl;

    Vector position;
    Vector velocity;
};

#endif /* Tank_hpp */
