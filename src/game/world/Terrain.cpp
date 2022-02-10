//
// Created by kevin on 10.02.2022.
//

#include "Terrain.h"

Terrain::Terrain(char *DetailMap1, float vertexGapSize, int chunkSize) {
    // Variablen übergeben
    graphService = new SinusGraph();
    this->vertexGapSize = vertexGapSize;
    this->chunkSize = chunkSize;
    this->worldCenter = 0.0;
    this->DetailMap1 = DetailMap1;

    // Ladevorgang starten
    this->createChunks();
}

Terrain::~Terrain() {
    this->deleteChunks();
    terrainList.clear();
    delete graphService;
}

// Speichert den Shader und übergibt diese den Chunks
void Terrain::shader(BaseShader *shader, bool deleteOnDestruction) {
    pShader = shader;
    for ( TerrainList::iterator it = terrainList.begin(); it != terrainList.end(); ++it) {
        (*it)->shader(shader, false);
    }
}

// Zeichnet alle Chunks
void Terrain::draw(const BaseCamera &Cam) {
    for ( TerrainList::iterator it = terrainList.begin(); it != terrainList.end(); ++it) {
        (*it)->draw(Cam);
    }
}

// Erstellt die Chunks anhand der Spielerposition
void Terrain::createChunks() {
    // Haupt-Chunk, wo sich der Spieler befindet
    int xPosChunkStart = worldCenter - fmod(worldCenter, chunkSize);
    terrainList.push_back(new TerrainChunk(
            graphService, xPosChunkStart, xPosChunkStart + chunkSize, vertexGapSize, DetailMap1));

    // Neben-Chunk, es wird die angrenzende Haupt-Chunk-Seite gewählt, die näher an dem Spieler ist
    if (fmod(worldCenter, chunkSize) < chunkSize / 2) {
        terrainList.push_back(new TerrainChunk(
                graphService, xPosChunkStart - chunkSize, xPosChunkStart, vertexGapSize, DetailMap1));
    }
    else {
        terrainList.push_back(new TerrainChunk(
                graphService, xPosChunkStart + chunkSize, xPosChunkStart + 2 * chunkSize, vertexGapSize, DetailMap1));
    }

    // Shader auf Chunks übergeben
    for ( TerrainList::iterator it = terrainList.begin(); it != terrainList.end(); ++it) {
        (*it)->shader(pShader, false);
    }
}

// Löscht aktuell bestehende Chunks
void Terrain::deleteChunks() {
    for ( TerrainList::iterator it = terrainList.begin(); it != terrainList.end(); ++it) {
        delete *it;
    }
    terrainList.clear();
}

// Schnittstelle zur Höhe f(x) einer x-Position
float Terrain::getHeight(float value_x) {
    return graphService->heightFunction(value_x);
}

// Schnittstelle zur Steigung f'(x) einer x-Position
float Terrain::getDerivation(float value_x) {
    return graphService->heightFunctionDerivation(value_x);
}

// Schnittstelle zur Änderung des Weltmittelpunktes, auf dessen Wert sich das Chunk Rendering stützt
void Terrain::changeWorldCenter(float addedValue) {
    // Grenze nach links erreicht?
    if (worldCenter + addedValue < 0.0)
        worldCenter = 0.0;
    else {
        // Prüfen, ob die Chunks neu berechnet werden müssen
        if (!((fmod(worldCenter, chunkSize) < chunkSize/2) ^ (fmod(worldCenter + addedValue, chunkSize) >= chunkSize / 2))) {
            this->worldCenter = worldCenter + addedValue;
            this->deleteChunks();
            this->createChunks();
        } else {
            this->worldCenter = worldCenter + addedValue;
        }

        // Welt-Verschiebung-Matrix erstellen und anwenden
        Matrix worldPosition;
        worldPosition.translation(Vector(-worldCenter, 0, 0));
        for ( TerrainList::iterator it = terrainList.begin(); it != terrainList.end(); ++it) {
            (*it)->transform(worldPosition);
        }
    }
}