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
    chunks.clear();
    delete graphService;
}

// Speichert den Shader und übergibt diese den Chunks
void Terrain::shader(BaseShader *shader, bool deleteOnDestruction) {
    pShader = shader;
    for (const auto &chunk : chunks)
        chunk->shader(shader, false);
}

// Zeichnet alle Chunks
void Terrain::draw(const BaseCamera &Cam) {
    for (const auto &chunk : chunks)
        chunk->draw(Cam);
}

// Erstellt die Chunks anhand der Spielerposition
void Terrain::createChunks() {
    // Haupt-Chunk, wo sich der Spieler befindet
    int xPosChunkStart = worldCenter - fmod(worldCenter, chunkSize);
    chunks.push_back(new TerrainChunk(
            graphService, xPosChunkStart, xPosChunkStart + chunkSize, vertexGapSize, DetailMap1));

    // Neben-Chunk, es wird die angrenzende Haupt-Chunk-Seite gewählt, die näher an dem Spieler ist
    if (fmod(worldCenter, chunkSize) < chunkSize / 2) {
        chunks.push_back(new TerrainChunk(
                graphService, xPosChunkStart - chunkSize, xPosChunkStart, vertexGapSize, DetailMap1));
    }
    else {
        chunks.push_back(new TerrainChunk(
                graphService, xPosChunkStart + chunkSize, xPosChunkStart + 2 * chunkSize, vertexGapSize, DetailMap1));
    }

    // Shader auf Chunks übergeben
    for (const auto &chunk : chunks)
        chunk->shader(pShader, false);
}

// Löscht aktuell bestehende Chunks
void Terrain::deleteChunks() {
    for (auto chunk : chunks)
        delete chunk;
    chunks.clear();
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
void Terrain::updateWorldCenter(float newWorldCenter) {
    // Prüfen, ob die Chunks neu berechnet werden müssen
    if (!((fmod(worldCenter, chunkSize) < chunkSize/2) ^ (fmod(newWorldCenter, chunkSize) >= chunkSize / 2))) {
        this->worldCenter = newWorldCenter;
        this->deleteChunks();
        this->createChunks();
    } else {
        this->worldCenter = newWorldCenter;
    }

    // Welt-Verschiebung-Matrix erstellen und anwenden
    Matrix worldPosition;
    worldPosition.translation(-worldCenter, 0, 0);
    for (const auto &chunk : chunks)
        chunk->transform(worldPosition);
}