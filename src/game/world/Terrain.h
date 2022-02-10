#ifndef COMPUTERGRAFIK_PRAKTIKUM_TERRAIN_H
#define COMPUTERGRAFIK_PRAKTIKUM_TERRAIN_H

#include <stdio.h>
#include <game/world/TerrainControlService.h>
#include "model/BaseModel.h"
#include "texture/Texture.h"
#include "buffer/VertexBuffer.h"
#include "buffer/IndexBuffer.h"
#include "GraphService.h"
#include "SinusGraph.h"

class Terrain : public BaseModel, virtual public TerrainControlService
{
public:
    Terrain(const char* DetailMap1, float minX, float maxX, float gap);
    virtual ~Terrain();
    bool load(const char* DetailMap1);

    virtual void shader( BaseShader* shader, bool deleteOnDestruction=false );
    virtual void draw(const BaseCamera& Cam);

    virtual float getHeight(float value_x);
    virtual float getDerivation(float value_x);
    virtual void setWorldCenter(float value_x);
protected:
    void applyShaderParameter();

    VertexBuffer VB;
    IndexBuffer IB;
    Texture DetailTex[1];

    GraphService* graphService = new SinusGraph();

    float minX, maxX, gap;
    const float minZ = -1;
    const float maxZ = 5;
};

#endif //COMPUTERGRAFIK_PRAKTIKUM_TERRAIN_H
