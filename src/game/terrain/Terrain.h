//
// Created by kevin on 10.02.2022.
//

#ifndef COMPUTERGRAFIK_PRAKTIKUM_TERRAIN_H
#define COMPUTERGRAFIK_PRAKTIKUM_TERRAIN_H


#include <list>
#include "game/terrain/renderer/GraphService.h"
#include "game/terrain/renderer/SinusGraph.h"
#include "TerrainChunk.h"
#include "game/terrain/renderer/PerlinGraph.h"
#include "game/terrain/renderer/FlatGraph.h"

class Terrain: public BaseModel, virtual public TerrainControlService
{
public:
    Terrain(char* assetDirectory, float vertexGapSize, int chunkSize);
    virtual ~Terrain();

    void shader( BaseShader* shader, bool deleteOnDestruction=false );
    void draw(const BaseCamera& Cam);

    void update();

    virtual float getHeight(float value_x);
    virtual float getDerivation(float value_x);
    virtual void setWorldCenter(float newWorldCenter);
    virtual void setWorldSize(float newWorldCenter);

protected:
    void shiftChunks();
    void distantChunks();

    typedef std::list<TerrainChunk*> TerrainChunkList;
    TerrainChunkList chunks;

    GraphService* graphService = new PerlinGraph();
    float vertexGapSize;
    int chunkSize;

    float actualWorldCenter;
    float oldWorldCenter;
    float actualWorldSize;
    float oldWorldSize;
};


#endif //COMPUTERGRAFIK_PRAKTIKUM_TERRAIN_H
