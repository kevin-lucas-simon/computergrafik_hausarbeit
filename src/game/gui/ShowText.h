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
#include "../../../libraries/glm/include/detail/type_vec3.hpp"

class ShowText: public BaseModel
{

public:

    ShowText(const std::string& text, float x, float y, float scale, glm::vec3 color);

    virtual ~ShowText();

    void shader(BaseShader* shader, bool deleteOnDestruction = false);

    void draw(const BaseCamera& Cam);
    void update();

    bool isDead();

protected:
    VertexBuffer VB;
    IndexBuffer IB;
    bool dead = false;
};