//
// Created by kevin on 10.02.2022.
//

#ifndef COMPUTERGRAFIK_PRAKTIKUM_TERRAIN_H
#define COMPUTERGRAFIK_PRAKTIKUM_TERRAIN_H


#include <shader/BaseShader.h>
#include <texture/Texture.h>
#include <list>
#include "GraphService.h"
#include "SinusGraph.h"
#include "TerrainChunk.h"
#include "texture/rgbimage.h"
#include "PerlinGraph.h"
#include "FlatGraph.h"

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

    const char* assetDirectory;
    float vertexGapSize;
    int chunkSize;

    float actualWorldCenter;
    float oldWorldCenter;
    float actualWorldSize;
    float oldWorldSize;
};


#endif //COMPUTERGRAFIK_PRAKTIKUM_TERRAIN_H
