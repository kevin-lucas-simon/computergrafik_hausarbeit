//
// Created by kevin on 10.02.2022.
//

#include "TerrainManager.h"
TerrainManager::TerrainManager(const char *DetailMap1, float vertexGapSize, int chunkSize) {
    terrain1 = new Terrain(new SinusGraph(), 0, chunkSize, vertexGapSize, DetailMap1);
    terrain2 = new Terrain(new SinusGraph(), -24, 0, vertexGapSize, DetailMap1);
}

TerrainManager::~TerrainManager() {}

void TerrainManager::shader(BaseShader *shader, bool deleteOnDestruction) {
    terrain1->shader(shader, deleteOnDestruction);
    terrain2->shader(shader, deleteOnDestruction);
}

void TerrainManager::draw(const BaseCamera &Cam) {
    terrain1->draw(Cam);
    terrain2->draw(Cam);
}

void TerrainManager::pushToModelList(std::list<BaseModel *> &ModelList) {
    ModelList.push_back(terrain1);
    ModelList.push_back(terrain2);
}

float TerrainManager::getHeight(float value_x) {
    return 0;
}

float TerrainManager::getDerivation(float value_x) {
    return 0;
}

void TerrainManager::setWorldCenter(float value_x) {
}