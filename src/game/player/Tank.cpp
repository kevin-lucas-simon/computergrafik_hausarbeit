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

void Tank::update(float dtime) {

}

void Tank::draw(const BaseCamera& Cam) {
    modelChassis->draw(Cam);
}
