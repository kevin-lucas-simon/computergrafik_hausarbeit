//
// Created by kevin on 09.02.2022.
//

#include <shader/TerrainShader.h>
#include "TerrainChunk.h"

TerrainChunk::TerrainChunk(GraphService* graphService, float minX, float maxX, float gap, const char* assetDirectory)
{
    this->graphService = graphService;
    this->minX = minX;
    this->maxX = maxX;
    this->gap = gap;
    this->assetDirectory = assetDirectory;

    bool loaded = load();
    if(!loaded)
        throw std::exception();
}

TerrainChunk::~TerrainChunk() {}

// Erstellt die Geometrie des Terrains
bool TerrainChunk::load()
{
    // Texturen laden
    if( !DetailTex[0].load(std::string().append(assetDirectory).append(detailTex0).data()) )
        return false;
    if( !DetailTex[1].load(std::string().append(assetDirectory).append(detailTex1).data()) )
        return false;
    // Height-Map erstellen
    RGBImage heightMap = new RGBImage();

    // Hilfsvariable: Anzahl Punkte im Chunk
    int iCount = (abs(maxX - minX)/gap)+1;
    int jCount = (abs(maxZ - minZ)/gap)+1;

    // iteriere durch alle Punkte im Chunk
    VB.begin();
    IB.begin();
    for (int i = 0; i < iCount; ++i) {
        for (int j = 0; j < jCount; ++j) {
            // Koordinatenpunkte ermitteln
            float iPos = i * gap + minX;
            float jPos = j * gap + minZ;

            // Index-Bufferberechnung mit Nachbar-Vertex aus der vorherigen Reihe
            if (i > 0 && j > 0) {
                IB.addIndex(jCount * i + j);
                IB.addIndex(jCount * i + j-1);
                IB.addIndex(jCount * (i-1) + j);

                IB.addIndex(jCount * (i-1) + j-1);
                IB.addIndex(jCount * (i-1) + j);
                IB.addIndex(jCount * i + j-1);
            }

            // Normalenberechnung mit Kreuzprodukt von f'(x) und g'(x)
            Vector fDerivate = Vector(1, graphService->heightFunctionDerivation(iPos), 0);
            Vector gDerivate = Vector(0, graphService->depthFunctionDerivation(jPos), 1);
            Vector normal = -fDerivate.cross(gDerivate).normalize();
            VB.addNormal(normal);

            // Texturkoordinaten
            VB.addTexcoord0(iPos, jPos / normal.dot(Vector(0, 1, 0)));
            VB.addTexcoord1(iPos, jPos / normal.dot(Vector(0, 1, 0)));

            // Setze Vertex mit Höhe-Funktionen zusammen
            VB.addVertex(iPos, graphService->heightFunction(iPos) + graphService->depthFunction(jPos), jPos);
        }
    }
    IB.end();
    VB.end();
    return true;
}

// Initialisierung des Shaders
void TerrainChunk::shader( BaseShader* shader, bool deleteOnDestruction )
{
    BaseModel::shader(shader, deleteOnDestruction);
}

// Wird in jedem Frame aufgerufen, um das Model zu zecihnen
void TerrainChunk::draw(const BaseCamera& Cam)
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

// Wendet die Shader Parameter an
void TerrainChunk::applyShaderParameter()
{
    TerrainShader* Shader = dynamic_cast<TerrainShader*>(BaseModel::shader());
    if(!Shader)
        return;

    Shader->mixTex(&MixTex);
    for(int i=0; i<2; i++)
        Shader->detailTex(i,&DetailTex[i]);
}

// Gibt die minX-Variable zurück
float TerrainChunk::getMinX() {
    return minX;
}

// Gibt die maxX-Variable zurück
float TerrainChunk::getMaxX() {
    return maxX;
}