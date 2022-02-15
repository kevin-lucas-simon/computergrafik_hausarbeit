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
    bool load();

    virtual void shader( BaseShader* shader, bool deleteOnDestruction=false );
    virtual void draw(const BaseCamera& Cam);

    float getMinX();
    float getMaxX();
protected:
    void applyShaderParameter();

    VertexBuffer VB;
    IndexBuffer IB;

    const char* assetDirectory;
    const char* detailTex0 = "grass.bmp";
    const char* detailTex1 = "rock.bmp";
    Texture DetailTex[2];
    Texture MixTex;

    GraphService* graphService;

    float minX, maxX, gap;
    const float minZ = -1;
    const float maxZ = 9;
};

#endif //COMPUTERGRAFIK_PRAKTIKUM_TERRAINCHUNK_H
