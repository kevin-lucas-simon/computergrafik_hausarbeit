//
// Created by Phileas Scheffer on 23.02.2022.
//

#include <map>
#include "framework/shader/BaseShader.h"

#ifndef COMPUTERGRAFIK_PRAKTIKUM_LOOSINGGUI_H
#define COMPUTERGRAFIK_PRAKTIKUM_LOOSINGGUI_H

#endif //COMPUTERGRAFIK_PRAKTIKUM_LOOSINGGUI_H

#include "framework/buffer/VertexBuffer.h"
#include "framework/model/BaseModel.h"
#include "framework/buffer/IndexBuffer.h"
#include "../../../libraries/glm/include/detail/type_vec3.hpp"
#include "../../../libraries/glm/include/detail/type_vec2.hpp"

class ShowText: public BaseModel
{

public:

    ShowText();

    virtual ~ShowText();

    void shader(BaseShader* shader, bool deleteOnDestruction = false);

    void draw(const BaseCamera &Cam);
    void update(const std::string& text, float x, float y, float scale, glm::vec3 color);

    bool isDead();

protected:
    VertexBuffer VB;
    IndexBuffer IB;
    bool dead = false;
    struct Character {
        unsigned int TextureID; // ID handle of the glyph texture
        glm::vec2 Size;      // Size of glyph
        glm::ivec2 Bearing;   // Offset from baseline to left/top of glyph
        unsigned int Advance;   // Horizontal offset to advance to next glyph
    };
    Character character;
    std::map<GLchar, Character> Characters;
    std::string text;
    float x;
    float y;
    float scale;
    glm::vec3 color;
};