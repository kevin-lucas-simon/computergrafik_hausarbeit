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
    // Position aktualisieren, mit Beachtung des Weltlimits
    position += velocity;
    if(position.X < 0) {
        position.X = 0;
        velocity.X = 0;
    }

    // Hilfsvariablen
    float terrainDerivation = terrainControl->getDerivation(position.X);
    float terrainHeight = terrainControl->getHeight(position.X);

    // Fallunterscheidung Bodenkontakt
    if (position.Y < terrainHeight + LIFT_HEIGHT) {
        // Auf dem Boden der Tatsachen bringen
        position.Y = terrainHeight;

        // Neigungsrichtung der Oberfläche ermitteln, die die Geschwindigkeit anhand des Einfallwinkels abbremst
        Vector slope = Vector(1, terrainDerivation, 0).normalize();
        velocity = velocity * (fabs(Vector(velocity).normalize().dot(slope)) * (1 - IMPACT_DRAG) + IMPACT_DRAG);

        // Geschwindigkeitsberechnung mit Fallunterscheidung der x-Richtung
        if(velocity.dot(Vector(1,0,0)) > 0.0) // x ist positiv
            velocity = slope * (velocity.length() - terrainDerivation * dTime * SLOPE_FORCE + keyFrontBack * dTime * USER_FORCE_DRIVING);
        else // x ist negativ
            velocity = -slope * (velocity.length() + terrainDerivation * dTime * SLOPE_FORCE - keyFrontBack * dTime * USER_FORCE_DRIVING);

        // Reibung simulieren
        velocity = velocity * GENERAL_DRAG;
    } else {
        // Gravitation auf fallendes Object anwenden samt Einwirkung des Spielers
        Vector gravity = Vector(0, -1, 0) * dTime * GRAVITY_FORCE;
        Vector userForce = Vector(0, -1, 0) * dTime * fabs(keyFrontBack) * USER_FORCE_FALLING;
        velocity = (velocity + gravity + userForce);
    }

    // Stoppen, wenn die Geschwindigkeit zu langsam ist
    if(velocity.length() < STOPPING_SPEED)
        velocity = Vector(0,0,0);

    // Welt-Center Variable aktualisieren
    terrainControl->updateWorldCenter(position.X);
}

void Tank::calculateTransformation() {
    // Nach aktueller Geschwindigkeitsrichtung ausrichten, bei keiner Geschwindigkeit wird nach der Welt ausgerichtet
    Matrix objectRotation;
    if (velocity.length() != 0) {
        float angle = acos(velocity.dot(Vector(1,0,0))*(1/velocity.length()));
        if(velocity.Y < 0)
            angle *= -1;
        if(velocity.X < 0)
            angle -= AI_MATH_PI;
        if(velocity.length() != 0)
            objectRotation.rotationZ(angle);
        else
            objectRotation.scale(1);
    } else {
        objectRotation.rotationZ(atan(terrainControl->getDerivation(position.X)));
    }

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