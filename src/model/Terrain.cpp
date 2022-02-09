#include "Terrain.h"
#include "texture/rgbimage.h"
#include "shader/Terrainshader.h"

Terrain::Terrain(const char* HeightMap, const char* DetailMap1, const char* DetailMap2,
                 const char* DetailMap3, const char* DetailMap4) : Size(10,1,10)
{
    if(HeightMap && DetailMap1 && DetailMap2 && DetailMap3 && DetailMap4)
    {
        bool loaded = load( HeightMap, DetailMap1, DetailMap2, DetailMap3, DetailMap4);
        if(!loaded)
            throw std::exception();
    }
}

Terrain::~Terrain()
{

}

bool Terrain::load( const char* HeightMap, const char* DetailMap1, const char* DetailMap2,
                    const char* DetailMap3, const char* DetailMap4)
{
    // Texturen laden
    if( !HeightTex.load(HeightMap) )
        return false;
    if( !DetailTex[0].load(DetailMap1) )
        return false;
    if( !DetailTex[1].load(DetailMap2) )
        return false;
    if( !DetailTex[2].load(DetailMap3) )
        return false;
    if( !DetailTex[3].load(DetailMap4) )
        return false;

    // Durch alle Pixel der HeightMap iterieren
    VB.begin();
    IB.begin();
    for (int i = 0; i < HeightTex.getRGBImage()->width(); ++i) {
        for (int j = 0; j < HeightTex.getRGBImage()->height(); ++j) {

            // Index-Bufferberechnung mit Nachbar-Vertex aus der vorherigen Reihe
            if(i > 0 && j > 0) {
                IB.addIndex(HeightTex.getRGBImage()->width() * i + j);
                IB.addIndex(HeightTex.getRGBImage()->width() * i + j-1);
                IB.addIndex(HeightTex.getRGBImage()->width() * (i-1) + j);

                IB.addIndex(HeightTex.getRGBImage()->width() * (i-1) + j-1);
                IB.addIndex(HeightTex.getRGBImage()->width() * (i-1) + j);
                IB.addIndex(HeightTex.getRGBImage()->width() * i + j-1);
            }

            // Ermittlung Normalvektor durch Mittelung der Flächen zu den Nachbarn
            if(i>0 && i<HeightTex.getRGBImage()->width()-1 && j>0 && j < HeightTex.getRGBImage()->height()-1) {
                Vector vecPosition = calcCoordinatesFromHeightMap(i, j);
                Vector vecNorth = calcCoordinatesFromHeightMap(i + 1, j) - vecPosition;
                Vector vecEast = calcCoordinatesFromHeightMap(i, j + 1) - vecPosition;
                Vector vecSouthEast = calcCoordinatesFromHeightMap(i - 1, j + 1) - vecPosition;
                Vector vecSouth = calcCoordinatesFromHeightMap(i - 1, j) - vecPosition;
                Vector vecWest = calcCoordinatesFromHeightMap(i, j - 1) - vecPosition;
                Vector vecNorthWest = calcCoordinatesFromHeightMap(i + 1, j - 1) - vecPosition;

                VB.addNormal((
                        vecNorth.cross(vecEast) +
                        vecEast.cross(vecSouthEast) +
                        vecSouthEast.cross(vecSouth) +
                        vecSouth.cross(vecWest) +
                        vecWest.cross(vecNorthWest) +
                        vecNorthWest.cross(vecNorth)
                        ) * (-1.0 / 6.0));
            } else
                VB.addNormal(0,0,0);

            // Texturkoordinaten
            float texS = 1.0f/HeightTex.getRGBImage()->width()*i;
            float texT = 1.0f/HeightTex.getRGBImage()->height()*j;
            VB.addTexcoord0(texS,texT);
            VB.addTexcoord1(texS,texT);

            // Setze Vertex anhand HeightMap Daten
            VB.addVertex(calcCoordinatesFromHeightMap(i, j));
        }
    }
    IB.end();
    VB.end();

    // MixMap Sobel Textur für Kantenerkennung
    RGBImage sobelTexture = RGBImage(HeightTex.getRGBImage()->width(), HeightTex.getRGBImage()->height());
    RGBImage::SobelFilter(sobelTexture, *HeightTex.getRGBImage(), 10);
    MixTex.create(sobelTexture);

    return true;
}

void Terrain::shader( BaseShader* shader, bool deleteOnDestruction )
{
    BaseModel::shader(shader, deleteOnDestruction);
}

void Terrain::draw(const BaseCamera& Cam)
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

void Terrain::applyShaderParameter()
{
    TerrainShader* Shader = dynamic_cast<TerrainShader*>(BaseModel::shader());
    if(!Shader)
        return;

    for(int i=0; i<4; i++)
        Shader->detailTex(i,&DetailTex[i]);
    Shader->scaling(Size);

    Shader->textureScale(TextureScale);
}

Vector Terrain::calcCoordinatesFromHeightMap(int x, int z) {
    return Vector(
            (this->width()/HeightTex.getRGBImage()->width()) * x - this->width()/2,
            HeightTex.getRGBImage()->getPixelColor(x,z).monochrome() * this->height(),
            (this->depth()/HeightTex.getRGBImage()->height()) * z - this->depth()/2
            );
}