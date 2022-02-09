#ifndef COMPUTERGRAFIK_PRAKTIKUM_PROZEDURALTERRAIN_H
#define COMPUTERGRAFIK_PRAKTIKUM_PROZEDURALTERRAIN_H

#include <stdio.h>
#include "basemodel.h"
#include "texture/texture.h"
#include "buffer/vertexbuffer.h"
#include "buffer/indexbuffer.h"

class ProzeduralTerrain : public BaseModel
{
public:
    ProzeduralTerrain(const char* DetailMap1, float minX, float maxX, float gap);
    virtual ~ProzeduralTerrain();
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
    const float minZ = -2;
    const float maxZ = 6;
};


#endif //COMPUTERGRAFIK_PRAKTIKUM_PROZEDURALTERRAIN_H
