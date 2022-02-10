//
// Created by kevin on 10.02.2022.
//

#include "TerrainManager.h"
TerrainManager::TerrainManager(char *DetailMap1, float vertexGapSize, int chunkSize) {
    // Variablen übergeben
    graphService = new SinusGraph();
    this->vertexGapSize = vertexGapSize;
    this->chunkSize = chunkSize;
    this->DetailMap1 = DetailMap1;

    // Ladevorgang starten
    this->createChunks();
}

TerrainManager::~TerrainManager() {
    this->deleteChunks();
    terrainList.clear();
    delete graphService;
}

void TerrainManager::shader(BaseShader *shader, bool deleteOnDestruction) {
    pShader = shader;
    for ( TerrainList::iterator it = terrainList.begin(); it != terrainList.end(); ++it) {
        (*it)->shader(shader, false);
    }
}

void TerrainManager::draw(const BaseCamera &Cam) {
    for ( TerrainList::iterator it = terrainList.begin(); it != terrainList.end(); ++it) {
        (*it)->draw(Cam);
    }
}

// Logik des Chunk Renderings
void TerrainManager::createChunks() {
    // Haupt-Chunk, wo sich der Spieler befindet
    int xPosChunkStart = worldCenter - fmod(worldCenter, chunkSize);
    terrainList.push_back(new Terrain(
            graphService, xPosChunkStart, xPosChunkStart + chunkSize, vertexGapSize, DetailMap1));

    // Neben-Chunk, es wird die angrenzende Haupt-Chunk-Seite gewählt, die näher an dem Spieler ist
    if (fmod(worldCenter, chunkSize) < chunkSize / 2)
        terrainList.push_back(new Terrain(
                graphService, xPosChunkStart - chunkSize, xPosChunkStart, vertexGapSize, DetailMap1));
    else
        terrainList.push_back(new Terrain(
                graphService, xPosChunkStart + chunkSize, xPosChunkStart + 2*chunkSize, vertexGapSize, DetailMap1));

    // Shader auf Chunks übergeben
    for ( TerrainList::iterator it = terrainList.begin(); it != terrainList.end(); ++it) {
        (*it)->shader(pShader, false);
    }
}

// Löscht aktuell bestehende Chunks
void TerrainManager::deleteChunks() {
    for (int i = 0; i < terrainList.size(); ++i) {
        delete terrainList.front();
        terrainList.pop_front();
    }
}

float TerrainManager::getHeight(float value_x) {
    return graphService->heightFunction(value_x);
}

float TerrainManager::getDerivation(float value_x) {
    return graphService->heightFunctionDerivation(value_x);
}

void TerrainManager::changeWorldCenter(float addedValue) {
    // Prüfen, ob die Chunks neu berechnet werden müssen
    if (fmod(worldCenter, chunkSize) != fmod(addedValue, chunkSize)) {
        this->worldCenter = worldCenter + addedValue;
        this->deleteChunks();
        this->createChunks();
    } else
        this->worldCenter = worldCenter + addedValue;
    std::cout << "worldCenter: " << worldCenter << std::endl;
}