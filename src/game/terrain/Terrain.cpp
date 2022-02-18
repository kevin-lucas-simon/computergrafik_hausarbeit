//
// Created by kevin on 10.02.2022.
//

#include "Terrain.h"

Terrain::Terrain(char *assetDirectory, float vertexGapSize, int chunkSize) {
    // Variablen übergeben
    this->vertexGapSize = vertexGapSize;
    this->chunkSize = chunkSize;
    this->actualWorldCenter = 0.0;
    this->actualWorldSize = chunkSize;
    this->assetDirectory = assetDirectory;

    // Haupt-Chunk generieren und anschließend alle anderen
    chunks.push_back(new TerrainChunk(this->assetDirectory, graphService, 0, chunkSize, vertexGapSize));
    chunks.front()->shader(pShader, false);
    this->distantChunks();
}

Terrain::~Terrain() {
    for (auto chunk : chunks)
        delete chunk;
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
    // Chunks aktualisieren
    this->shiftChunks();
    this->distantChunks();

    // Welt-Verschiebung-Matrix erstellen und anwenden
    Matrix worldPosition = Matrix().translation(-actualWorldCenter, 0, 0);
    for (const auto &chunk : chunks)
        chunk->transform(worldPosition);
}

// Erstellt Chunk an einer Seite, löscht ein Chunk an anderer Seite, wenn ein neuer Chunk betreten wurde
void Terrain::shiftChunks() {
    // Prüfen, ob in der Zwischenzeit ein anderer Chunk betreten wurde
    if ((int) oldWorldCenter / chunkSize != (int) actualWorldCenter / chunkSize) {
        // Rechter Chunk wurde betreten
        if (actualWorldCenter - chunks.front()->getMinX() > chunks.back()->getMaxX() - actualWorldCenter) {
            chunks.push_back(new TerrainChunk(this->assetDirectory, graphService,
                  chunks.back()->getMaxX(), chunks.back()->getMaxX() + chunkSize, vertexGapSize));
            chunks.back()->shader(pShader, false);
            delete chunks.front();
            chunks.pop_front();
        }
        // Linker Chunk wurde betreten
        else {
            chunks.push_front(new TerrainChunk(this->assetDirectory, graphService,
                   chunks.front()->getMinX() - chunkSize, chunks.front()->getMinX(), vertexGapSize));
            chunks.front()->shader(pShader, false);
            delete chunks.back();
            chunks.pop_back();
        }
    }
}

// Erstellt bzw. löscht Chunks am Rand, wenn sich der Chunkrendering-Bereich ändert
void Terrain::distantChunks() {
    // Prüfen, ob sich der Chunkrendering-Bereich geändert hat
    int chunkDifference = ((int) actualWorldSize / chunkSize - (int) oldWorldSize / chunkSize);
    if (chunkDifference != 0) {
        // Chunks hinzufügen, wenn der Chunkrendering-Bereich größer wird
        if(chunkDifference > 0) {
            while (chunks.size() < (int) actualWorldSize / chunkSize + 1) {
                chunks.push_front(new TerrainChunk(this->assetDirectory, graphService,
                       chunks.front()->getMinX()-chunkSize, chunks.front()->getMinX(), vertexGapSize));
                chunks.push_back(new TerrainChunk(this->assetDirectory, graphService,
                       chunks.back()->getMaxX(), chunks.back()->getMaxX() + chunkSize, vertexGapSize));
                chunks.front()->shader(pShader, false);
                chunks.back()->shader(pShader, false);
            }
        }
        // Chunks entfernen, wenn der Chunkrendering-Bereich kleiner wird
        else {
            while (chunks.size() > (int) actualWorldSize / chunkSize + 2) {
                delete chunks.front();
                delete chunks.back();
                chunks.pop_front();
                chunks.pop_back();
            }
        }
        // Alte Weltgröße mit aktuellem Wert besetzen, da die Weltgröße nicht in jedem Frame angepasst wird
        oldWorldSize = actualWorldSize;
    }
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
    oldWorldSize = actualWorldSize;
    if(newWorldSize < chunkSize) // Minimalwert der Weltgröße
        actualWorldSize = chunkSize;
    else
        actualWorldSize = newWorldSize;
}