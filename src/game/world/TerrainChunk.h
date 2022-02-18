#ifndef COMPUTERGRAFIK_PRAKTIKUM_TERRAINCHUNK_H
#define COMPUTERGRAFIK_PRAKTIKUM_TERRAINCHUNK_H

#include <stdio.h>
#include <game/world/TerrainControlService.h>
#include <framework/shader/BaseShader.h>
#include <framework/camera/Camera.h>
#include <game/world/renderer/GraphService.h>
#include <framework/buffer/VertexBuffer.h>
#include <framework/buffer/IndexBuffer.h>
#include <framework/texture/Texture.h>
#include <framework/model/BaseModel.h>

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

    GraphService* graphService;

    float minX, maxX, gap;
    const float minZ = -1;
    const float maxZ = 9;
};

#endif //COMPUTERGRAFIK_PRAKTIKUM_TERRAINCHUNK_H
