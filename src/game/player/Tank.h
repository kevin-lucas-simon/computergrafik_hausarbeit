//
// Created by kevin on 11.02.2022.
//

#ifndef Tank_hpp
#define Tank_hpp

#include <stdio.h>
#include "model/Model.h"

class Tank : public BaseModel
{
public:
    Tank();
    virtual ~Tank();
    bool loadModels(const char* ChassisFile, const char* CannonFile);
    void update(float dtime);
    virtual void draw(const BaseCamera& Cam);
protected:
    Model* modelChassis;
};

#endif /* Tank_hpp */
