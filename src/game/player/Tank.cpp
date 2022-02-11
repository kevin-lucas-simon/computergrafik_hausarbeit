//
// Created by kevin on 11.02.2022.
//

#include <shader/PhongShader.h>
#include "Tank.h"


Tank::Tank() {
    position = Vector(0,0,0);
    velocity = Vector(0,0,0);
}

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
    // Hilfsvariablen
    float terrainDerivation = terrainControl->getDerivation(position.X);

    // Physikalische Kräfte ermitteln
    Vector userForce = Vector(1, 0, 0) * keyFrontBack * 0.15;
    Vector gravitation = Vector(0,-1,0);
    Vector slope = Vector(0,terrainDerivation,0);
    if(terrainDerivation < 0)
        slope.X = 1;
    else
        slope.X = -1;
    slope = slope * 0.1;

    // Geschwindigkeit berechnen
    velocity = velocity + userForce * dTime + slope * dTime;

    // Reibung simulieren
    velocity = velocity * 0.995;
//    if(velocity.lengthSquared() > -0.0000001 && velocity.lengthSquared() < 0.0000001)
//        velocity = Vector(0,0,0);

    // Neue Position ermitteln
    position = position + velocity;
    if(position.Y < terrainDerivation)
        position.Y = terrainDerivation;

    // Welt-Center Variable aktualisieren
    if(position.X < 0) {
        position.X = 0.0;
    }
    terrainControl->updateWorldCenter(position.X);

    // Objektposition anhand der Welt ausrichten
    Matrix objectRotation;
    objectRotation.rotationZ(atan(terrainControl->getDerivation(position.X)));
    Matrix objectTranslation;
    objectTranslation.translation(0, terrainControl->getHeight(position.X), 0);
    modelChassis->transform(objectTranslation * objectRotation);
}

void Tank::draw(const BaseCamera& Cam) {
    modelChassis->draw(Cam);
}
