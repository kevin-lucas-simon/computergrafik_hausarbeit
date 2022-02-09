//
// Created by kevin on 09.02.2022.
//

#include <shader/TerrainShader.h>
#include "ProzeduralTerrain.h"
ProzeduralTerrain::ProzeduralTerrain(const char* DetailMap1) : Size(10,1,10)
{
    if(DetailMap1)
    {
        bool loaded = load( DetailMap1);
        if(!loaded)
            throw std::exception();
    }
}

ProzeduralTerrain::~ProzeduralTerrain()
{

}

bool ProzeduralTerrain::load( const char* DetailMap1)
{
    // Texturen laden
    if( !DetailTex[0].load(DetailMap1) )
        return false;

    // Durch alle Pixel der HeightMap iterieren
    VB.begin();
    IB.begin();

    // TODO
    VB.addNormal(0,1,0);
    VB.addTexcoord0(0,0);
    VB.addVertex(0,0,0);

    VB.addNormal(0,1,0);
    VB.addTexcoord0(1,0);
    VB.addVertex(0,0,3);

    VB.addNormal(0,1,0);
    VB.addTexcoord0(0,1);
    VB.addVertex(5,0,0);

    IB.addIndex(0);
    IB.addIndex(1);
    IB.addIndex(2);

    IB.end();
    VB.end();

    return true;
}

void ProzeduralTerrain::shader( BaseShader* shader, bool deleteOnDestruction )
{
    BaseModel::shader(shader, deleteOnDestruction);
}

void ProzeduralTerrain::draw(const BaseCamera& Cam)
{
    applyShaderParameter();
    BaseModel::draw(Cam);

    // Zeichne alle Vertex anhand des Index-Buffers ein
    VB.activate();
    IB.activate();

    glDrawElements(GL_TRIANGLES, IB.indexCount(), IB.indexFormat(), 0);

    IB.deactivate();
    VB.deactivate();
}

void ProzeduralTerrain::applyShaderParameter()
{
    TerrainShader* Shader = dynamic_cast<TerrainShader*>(BaseModel::shader());
    if(!Shader)
        return;

    for(int i=0; i<1; i++)
        Shader->detailTex(i,&DetailTex[i]);
    Shader->scaling(Size);
}