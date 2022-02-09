//
//  Tank.hpp
//  CGXcode
//
//  Created by Philipp Lensing on 16.11.16.
//  Copyright © 2016 Philipp Lensing. All rights reserved.
//

#ifndef Tank_hpp
#define Tank_hpp

#include <stdio.h>
#include "model/model.h"

class Tank : public BaseModel
{
public:
    Tank();
    virtual ~Tank();
    bool loadModels(const char* ChassisFile, const char* CannonFile);
    void steer( float ForwardBackward, float LeftRight);
    void aim( const Vector& Target );
    void update(float dtime);
    virtual void draw(const BaseCamera& Cam);
protected:
    Model* modelChassis;
    Model* modelCannon;

    float velocityForwardBackward = 0;
    float velocityLeftRight = 0;

    Matrix transformBot;
    Vector mouseTarget = Vector(0,0,0);
};

#endif /* Tank_hpp */
