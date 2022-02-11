//
// Created by kevin on 11.02.2022.
//

#include <shader/PhongShader.h>
#include "Tank.h"


Tank::Tank() {}

Tank::~Tank() {
    delete modelChassis;
}

bool Tank::loadModels(const char* ChassisFile, const char* CannonFile) {
    modelChassis = new Model(ChassisFile, false);
    modelChassis->shader(pShader, true);
    return true;
}

void Tank::bindToTerrain(TerrainControlService* terrainControl) {
    this->terrainControl = terrainControl;
}

void Tank::update(float dTime, int keyFrontBack) {
    // Welt-Center Variable aktualisieren
    worldPosition += dTime * keyFrontBack * 2;
    if(worldPosition < 0)
        worldPosition = 0.0;
    terrainControl->updateWorldCenter(worldPosition);

    // Objektposition anhand der Welt ausrichten
    Matrix objectRotation;
    objectRotation.rotationZ(atan(terrainControl->getDerivation(worldPosition)));
    Matrix objectTranslation;
    objectTranslation.translation(0, terrainControl->getHeight(worldPosition), 0);
    modelChassis->transform(objectTranslation * objectRotation);
}

void Tank::draw(const BaseCamera& Cam) {
    modelChassis->draw(Cam);
}
