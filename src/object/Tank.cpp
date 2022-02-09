//
//  Tank.cpp
//  CGXcode
//
//  Created by Philipp Lensing on 16.11.16.
//  Copyright © 2016 Philipp Lensing. All rights reserved.
//

#include <shader/PhongShader.h>
#include "Tank.h"


Tank::Tank()
{
    transformBot.translation(0,0,0);
}

Tank::~Tank()
{
    delete modelCannon;
    delete modelChassis;
}

bool Tank::loadModels(const char* ChassisFile, const char* CannonFile)
{
    modelChassis = new Model(ChassisFile, false);
    modelChassis->shader(pShader, true);

    modelCannon = new Model(CannonFile, false);
    modelCannon->shader(pShader, true);
    return true;
}

void Tank::steer( float ForwardBackward, float LeftRight)
{
    velocityForwardBackward = ForwardBackward * 2.5f;
    velocityLeftRight = LeftRight;
}

void Tank::aim(const Vector& Target )
{
    mouseTarget = Target;
}

void Tank::update(float dtime)
{
    // Rotation links/rechts
    Matrix matBotRotation;
    matBotRotation.rotationY(velocityLeftRight * dtime);

    // Bewegung vorne/hinten
    Matrix matBotForward;
    matBotForward.translation(velocityForwardBackward*dtime,0,0);

    // Auf Unterteil anwenden
    transformBot = transformBot * matBotForward * matBotRotation;
    modelChassis->transform(transformBot);

    // Kanonenrohr auf Mauszeiger ausrichten
    Matrix matTopPosition;
    matTopPosition.lookAt(mouseTarget, Vector(0, 1, 0), transformBot.translation());
    matTopPosition.invert();

    // Kanonenrohr Position korrigieren
    Matrix matTopRotation;
    matTopRotation.rotationY(AI_MATH_HALF_PI);

    // Auf Oberteil anwenden
    modelCannon->transform(matTopPosition * matTopRotation);
}

void Tank::draw(const BaseCamera& Cam)
{
    modelChassis->draw(Cam);
    modelCannon->draw(Cam);
}
