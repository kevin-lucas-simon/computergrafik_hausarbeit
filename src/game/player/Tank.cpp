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
    calculatePhysics(dTime, keyFrontBack);
    calculateTransformation();
}

void Tank::draw(const BaseCamera& Cam) {
    modelChassis->draw(Cam);
}

void Tank::calculatePhysics(float dTime, int keyFrontBack) {
    // Position aktualisieren
    position += velocity;

    // Hilfsvariablen
    float terrainDerivation = terrainControl->getDerivation(position.X);
    float terrainHeight = terrainControl->getHeight(position.X);

    // Fallunterscheidung Bodenkontakt
    if (position.Y < terrainHeight + 0.05) {
        // Auf dem Boden der Tatsachen bringen
        position.Y = terrainHeight;

        // Steigung der Oberfläche ermitteln
        Vector slope = Vector(1, terrainDerivation, 0);

        // Geschwindigkeitsberechnung mit Fallunterscheidung der x-Richtung
        if(velocity.dot(Vector(1,0,0)) > 0.0) // x ist positiv
            velocity = slope.normalize() * (velocity.length() - terrainDerivation * dTime + keyFrontBack * dTime );
        else // x ist negativ
            velocity = -slope.normalize() * (velocity.length() + terrainDerivation * dTime - keyFrontBack * dTime);
    } else {
        // Gravitation auf fallendes Object anwenden
        Vector gravity = Vector(0, -1, 0) * dTime;
        velocity = (velocity + gravity);
    }

    // Welt-Center Variable aktualisieren
    terrainControl->updateWorldCenter(position.X);
}

void Tank::calculateTransformation() {
    // Nach aktueller Geschwindigkeitsrichtung ausrichten
    Matrix objectRotation;
    float angle = acos(velocity.dot(Vector(1,0,0))*(1/velocity.length()));
    if(velocity.Y < 0)
        angle *= -1;
    if(velocity.X < 0)
        angle -= AI_MATH_PI;
    objectRotation.rotationZ(angle);

    // In verkehrter Richtung drehen beim Rückwärts fahren
    Matrix objectDirection;
    if(velocity.X < 0)
        objectDirection.rotationY(AI_MATH_PI);
    else
        objectDirection.scale(1);

    // Höhe ausrichten
    Matrix objectTranslation;
    objectTranslation.translation(0, position.Y, 0);

    // Transformation anwenden
    modelChassis->transform(objectTranslation * objectRotation * objectDirection);
}