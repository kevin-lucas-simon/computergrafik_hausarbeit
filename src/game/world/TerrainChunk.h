#ifndef COMPUTERGRAFIK_PRAKTIKUM_TERRAINCHUNK_H
#define COMPUTERGRAFIK_PRAKTIKUM_TERRAINCHUNK_H

#include <stdio.h>
#include <game/world/TerrainControlService.h>
#include "model/BaseModel.h"
#include "texture/Texture.h"
#include "buffer/VertexBuffer.h"
#include "buffer/IndexBuffer.h"
#include "GraphService.h"

class TerrainChunk : public BaseModel
{
public:
    TerrainChunk(GraphService* graphService, float minX, float maxX, float vertexGapSize, const char* DetailMap1);
    virtual ~TerrainChunk();
    bool load(const char* DetailMap1);

    virtual void shader( BaseShader* shader, bool deleteOnDestruction=false );
    virtual void draw(const BaseCamera& Cam);

    float getMinX();
    float getMaxX();
protected:
    void applyShaderParameter();

    VertexBuffer VB;
    IndexBuffer IB;
    Texture DetailTex[1];

    GraphService* graphService;

    float minX, maxX, gap;
    const float minZ = -1;
    const float maxZ = 5;
};

#endif //COMPUTERGRAFIK_PRAKTIKUM_TERRAINCHUNK_H
