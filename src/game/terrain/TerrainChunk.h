#ifndef COMPUTERGRAFIK_PRAKTIKUM_TERRAINCHUNK_H
#define COMPUTERGRAFIK_PRAKTIKUM_TERRAINCHUNK_H

#include <stdio.h>
#include <game/terrain/TerrainControlService.h>
#include <framework/shader/BaseShader.h>
#include <framework/camera/Camera.h>
#include <game/terrain/renderer/GraphService.h>
#include <framework/buffer/VertexBuffer.h>
#include <framework/buffer/IndexBuffer.h>
#include <framework/texture/Texture.h>
#include <framework/model/BaseModel.h>

class TerrainChunk : public BaseModel
{
public:
    TerrainChunk(const char* assetDirectory, GraphService* graphService, float minX, float maxX, float vertexGapSize);
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

    const char* grassTextureFile = "models/terrain/grass.bmp";
    const char* rockTextureFile = "models/terrain/rock.bmp";
    Texture DetailTex[2];

    GraphService* graphService;

    float minX, maxX, gap;
    const float minZ = -1;
    const float maxZ = 9;
};

#endif //COMPUTERGRAFIK_PRAKTIKUM_TERRAINCHUNK_H
