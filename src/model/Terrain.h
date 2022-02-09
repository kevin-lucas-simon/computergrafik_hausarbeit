#ifndef COMPUTERGRAFIK_PRAKTIKUM_TERRAIN_H
#define COMPUTERGRAFIK_PRAKTIKUM_TERRAIN_H

#include <stdio.h>
#include "basemodel.h"
#include "texture/texture.h"
#include "buffer/vertexbuffer.h"
#include "buffer/indexbuffer.h"

class Terrain : public BaseModel
{
public:
    Terrain(const char* DetailMap1, float minX, float maxX, float gap);
    virtual ~Terrain();
    bool load(const char* DetailMap1);

    virtual void shader( BaseShader* shader, bool deleteOnDestruction=false );
    virtual void draw(const BaseCamera& Cam);

protected:
    void applyShaderParameter();
    float heightFunction(float valueX);
    float heightFunctionDerivation(float valueX);
    float depthFunction(float valueZ);
    float depthFunctionDerivation(float valueZ);

    VertexBuffer VB;
    IndexBuffer IB;
    Texture DetailTex[1];

    float minX, maxX, gap;
    const float minZ = -1;
    const float maxZ = 5;
};


#endif //COMPUTERGRAFIK_PRAKTIKUM_TERRAIN_H
