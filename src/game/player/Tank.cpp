//
// Created by kevin on 11.02.2022.
//

#include "Tank.h"


Tank::Tank(char *assetDirectory, TerrainControlService* terrainControl) {
    // Parameter übertragen
    this->assetDirectory = assetDirectory;
    this->terrainControl = terrainControl;

    // Modelle laden
    modelChassis = new Model(std::string().append(assetDirectory).append(chassisFile).data(), false);
    modelCannon = new Model(std::string().append(assetDirectory).append(cannonFile).data(), false);

    // Physik initialisieren
    position = Vector(0,0,0);
    velocity = Vector(0,0,0);
}

Tank::~Tank() {
    delete modelChassis;
    delete modelCannon;
}

void Tank::shader(BaseShader *shader, bool deleteOnDestruction) {
    this->pShader = shader;
    modelChassis->shader(pShader, deleteOnDestruction);
    modelCannon->shader(pShader, deleteOnDestruction);
}

void Tank::draw(const BaseCamera& Cam) {
    modelChassis->draw(Cam);
    modelCannon->draw(Cam);
}

void Tank::update(float dTime, int keyForward, int keyBackward) {
    calculatePhysics(dTime, keyForward, keyBackward);
    calculateTransformation();
}

void Tank::calculatePhysics(float dTime, int keyForward, int keyBackward) {
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
            velocity = slope * (velocity.length()
                    - std::max(0.0f, terrainDerivation) * dTime * SLOPE_FORCE_UPWARD
                    - std::min(terrainDerivation, 0.0f) * dTime * SLOPE_FORCE_DOWNWARD
                    + keyForward * dTime * USER_FORCE_DRIVING);
        else // x ist negativ
            velocity = -slope * (velocity.length()
                    + std::max(0.0f, terrainDerivation) * dTime * SLOPE_FORCE_UPWARD
                    + std::min(terrainDerivation, 0.0f) * dTime * SLOPE_FORCE_DOWNWARD
                    - keyForward * dTime * USER_FORCE_DRIVING);

        // Reibung simulieren
        velocity = velocity * GENERAL_DRAG;
    } else {
        // Gravitation auf fallendes Object anwenden samt Einwirkung des Spielers
        Vector gravity = Vector(0, -1, 0) * dTime * GRAVITY_FORCE;
        Vector userForceFalling = Vector(0, -1, 0) * dTime * keyBackward * USER_FORCE_FALLING;
        Vector userForceGliding = Vector(0, 1, 0) * dTime * keyForward * USER_FORCE_GLIDING;
        velocity = (velocity + gravity + userForceFalling + userForceGliding);
    }

    // Stoppen, wenn die Geschwindigkeit zu langsam ist
    if(velocity.length() < MINIMUM_SPEED) velocity = Vector(0, 0, 0);

    // Geschwindigkeit auf Maximalgeschwindigkeit begrenzen, falls diese überschritten wird
    if(velocity.length() > MAXIMUM_SPEED) velocity = velocity.normalize() * MAXIMUM_SPEED;

    // Welt-Center Variable aktualisieren
    terrainControl->setWorldCenter(position.X);
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
    Matrix finalTransformation = objectTranslation * objectRotation * objectDirection;
    modelChassis->transform(finalTransformation);
    modelCannon->transform(finalTransformation);
}

// Schnittstelle zur Höhe des Spielers
float Tank::getHeight() {
    return position.Y;
}

// Schnittstelle zur Position des Spielers
float Tank::getPosition() {
    return position.X;
}

// Schnittstelle zur Geschwindigkeit des Spielers
float Tank::getSpeed() {
    return velocity.length();
}