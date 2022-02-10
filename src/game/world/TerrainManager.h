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

class TerrainManager: public BaseModel, virtual public TerrainControlService
{
public:
    TerrainManager(char* DetailMap1, float vertexGapSize, int chunkSize);
    virtual ~TerrainManager();

    void shader( BaseShader* shader, bool deleteOnDestruction=false );
    void draw(const BaseCamera& Cam);

    virtual float getHeight(float value_x);
    virtual float getDerivation(float value_x);
    virtual void changeWorldCenter(float addedValue);

protected:
    void createChunks();
    void deleteChunks();

    typedef std::list<Terrain*> TerrainList;
    TerrainList terrainList;
    GraphService* graphService;

    char *DetailMap1;
    float vertexGapSize;
    float worldCenter;
    int chunkSize;
};


#endif //COMPUTERGRAFIK_PRAKTIKUM_TERRAINMANAGER_H
