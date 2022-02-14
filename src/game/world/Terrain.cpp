//
// Created by kevin on 10.02.2022.
//

#include "Terrain.h"
#include "FlatGraph.h"

Terrain::Terrain(char *DetailMap1, float vertexGapSize, int chunkSize) {
    // Variablen übergeben
    graphService = new FlatGraph();
    this->vertexGapSize = vertexGapSize;
    this->chunkSize = chunkSize;
    this->actualWorldCenter = 0.0;
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

// Wird in jedem Frame aufgerufen
void Terrain::update() {
    // Prüfen, ob in der Zwischenzeit ein anderer Chunk betreten wurde
    if ((int) oldWorldCenter / chunkSize != (int) actualWorldCenter / chunkSize)
        this->shiftChunks();

    // Welt-Verschiebung-Matrix erstellen und anwenden
    Matrix worldPosition = Matrix().translation(-actualWorldCenter, 0, 0);
    for (const auto &chunk : chunks)
        chunk->transform(worldPosition);
}

// Erstellt die Chunks anhand der Spielerposition
void Terrain::createChunks() {
    // Haupt-Chunk
    chunks.push_back(new TerrainChunk(graphService, 0, chunkSize, vertexGapSize, DetailMap1));
    // Neben-Chunks
    chunks.push_front(new TerrainChunk(
            graphService, chunks.front()->getMinX()-chunkSize, chunks.front()->getMinX(), vertexGapSize, DetailMap1));
    chunks.push_back(new TerrainChunk(
            graphService, chunks.back()->getMaxX(), chunks.back()->getMaxX() + chunkSize, vertexGapSize, DetailMap1));

    // Shader auf Chunks übergeben
    for (const auto &chunk : chunks)
        chunk->shader(pShader, false);
}

// Erstellt Chunk an einer Seite, löscht ein Chunk an anderer Seite, wenn ein neuer Chunk betreten wurde
void Terrain::shiftChunks() {
    // Rechter Chunk wurde betreten
    if (actualWorldCenter - chunks.front()->getMinX() > chunks.back()->getMaxX() - actualWorldCenter) {
        chunks.push_back(new TerrainChunk(
                graphService, chunks.back()->getMaxX(), chunks.back()->getMaxX() + chunkSize,
                vertexGapSize, DetailMap1));
        chunks.back()->shader(pShader, false);
        delete chunks.front();
        chunks.pop_front();
    }
    // Linker Chunk wurde betreten
    else {
        chunks.push_front(new TerrainChunk(
                graphService, chunks.front()->getMinX() - chunkSize, chunks.front()->getMinX(),
                vertexGapSize, DetailMap1));
        chunks.front()->shader(pShader, false);
        delete chunks.back();
        chunks.pop_back();
    }
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
void Terrain::setWorldCenter(float newWorldCenter) {
    oldWorldCenter = actualWorldCenter;
    actualWorldCenter = newWorldCenter;
}

// Schnittstelle zur Änderung der gerenderten Weltgröße, auf dessen Wert sich das Chunk Rendering stützt
void Terrain::setWorldSize(float newWorldSize) {
    worldSize = newWorldSize;
}