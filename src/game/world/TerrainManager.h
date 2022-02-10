//
// Created by kevin on 10.02.2022.
//

#ifndef COMPUTERGRAFIK_PRAKTIKUM_TERRAINMANAGER_H
#define COMPUTERGRAFIK_PRAKTIKUM_TERRAINMANAGER_H


#include <shader/BaseShader.h>
#include <texture/Texture.h>
#include <list>
#include "GraphService.h"
#include "SinusGraph.h"
#include "Terrain.h"

class TerrainManager: virtual public TerrainControlService
{
public:
    TerrainManager(const char* DetailMap1, float vertexGapSize, int chunkSize);
    virtual ~TerrainManager();

    void shader( BaseShader* shader, bool deleteOnDestruction=false );
    void draw(const BaseCamera& Cam);
    void pushToModelList(std::list<BaseModel*>& ModelList);


    virtual float getHeight(float value_x);
    virtual float getDerivation(float value_x);
    virtual void setWorldCenter(float value_x);

protected:
    Texture DetailTex[1];
    GraphService* graphService = new SinusGraph();
    Terrain* terrain1;
    Terrain* terrain2;

    float gapSize;
};


#endif //COMPUTERGRAFIK_PRAKTIKUM_TERRAINMANAGER_H
