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
    ProzeduralTerrain(const char* DetailMap1=NULL);
    virtual ~ProzeduralTerrain();
    bool load(const char* DetailMap1);

    virtual void shader( BaseShader* shader, bool deleteOnDestruction=false );
    virtual void draw(const BaseCamera& Cam);

    float width() const { return Size.X; }
    float height() const { return Size.Y; }
    float depth() const { return Size.Z; }

    void width(float v) { Size.X = v; }
    void height(float v) { Size.Y = v; }
    void depth(float v) { Size.Z = v; }

    const Vector& size() const { return Size; }
    void size(const Vector& s) { Size = s; }
protected:
    void applyShaderParameter();

    VertexBuffer VB;
    IndexBuffer IB;
    Texture DetailTex[1];
    Vector Size;
};


#endif //COMPUTERGRAFIK_PRAKTIKUM_PROZEDURALTERRAIN_H
