//
// Created by kevin on 10.02.2022.
//

#ifndef COMPUTERGRAFIK_PRAKTIKUM_TERRAINCONTROLSERVICE_H
#define COMPUTERGRAFIK_PRAKTIKUM_TERRAINCONTROLSERVICE_H


class TerrainControlService
{
public:
    virtual float getHeight(float value_x) = 0;
    virtual float getDerivation(float value_x) = 0;
    virtual void setWorldCenter(float value_x) = 0;
};


#endif //COMPUTERGRAFIK_PRAKTIKUM_TERRAINCONTROLSERVICE_H
