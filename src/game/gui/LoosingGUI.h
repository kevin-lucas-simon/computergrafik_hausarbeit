//
// Created by Phileas Scheffer on 23.02.2022.
//

#include "framework/shader/BaseShader.h"

#ifndef COMPUTERGRAFIK_PRAKTIKUM_LOOSINGGUI_H
#define COMPUTERGRAFIK_PRAKTIKUM_LOOSINGGUI_H

#endif //COMPUTERGRAFIK_PRAKTIKUM_LOOSINGGUI_H

#include "framework/buffer/VertexBuffer.h"
#include "framework/model/BaseModel.h"
#include "framework/buffer/IndexBuffer.h"

class LoosingGUI: public BaseModel
{

public:
    LoosingGUI(const std::string& AssetDirectory);
    virtual ~LoosingGUI();

    void shader(BaseShader* shader, bool deleteOnDestruction = false);

    void draw(const BaseCamera& Cam);
    void update();

    bool isDead();

protected:
    VertexBuffer VB;
    IndexBuffer IB;
    bool dead = false;
};