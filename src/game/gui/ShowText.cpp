//
// Created by Phileas Scheffer on 23.02.2022.
//

#include "ShowText.h"
#include "framework/model/BaseModel.h"
#include "GL/glut.h"
#include "game/shader/GUIShader.h"
#include "../../../libraries/glm/include/vec3.hpp"
#include "../../../libraries/glm/include/detail/type_vec2.hpp"
#include <map>
#include <ft2build.h>
#include <iostream>
#include FT_FREETYPE_H

ShowText::ShowText() {

    FT_Library ft;
    if (FT_Init_FreeType(&ft))
    {
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
    }


    FT_Face face;
    if (FT_New_Face(ft, "C:/Users/saeli/Documents/GitHub/computergrafik_hausarbeit/src/game/gui/arialbd.ttf", 0, &face))
    {
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
    }
    FT_Set_Pixel_Sizes(face, 0, 48);


    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction

    for (unsigned char c = 0; c < 128; c++)
    {
        // load character glyph
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
            continue;
        }
        // generate texture
        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RED,
                face->glyph->bitmap.width,
                face->glyph->bitmap.rows,
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                face->glyph->bitmap.buffer
        );
        // set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // now store character for later use
        Character character = {
                texture,
                glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                static_cast<unsigned int>(face->glyph->advance.x)
        };
        Characters.insert(std::pair<char, Character>(c, character));
    }

    FT_Done_Face(face);
    FT_Done_FreeType(ft);


}

ShowText::~ShowText(){

};

void ShowText::draw(const BaseCamera &Cam) {
    BaseModel::draw(Cam);


    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++) {

        Character ch = Characters[*c];

        std::cout << "TexID-->" << ch.TextureID << std::endl;
        std::cout << "Advance-->" << ch.Advance << std::endl;

        float xpos = x + ch.Bearing.x * scale;
        float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

        float w = ch.Size.x * scale;
        float h = ch.Size.y * scale;
        // update VBO for each character
        float vertices[6][4] = {
                {xpos,     ypos + h, 0.0f, 0.0f},
                {xpos,     ypos,     0.0f, 1.0f},
                {xpos + w, ypos,     1.0f, 1.0f},

                {xpos,     ypos + h, 0.0f, 0.0f},
                {xpos + w, ypos,     1.0f, 1.0f},
                {xpos + w, ypos + h, 1.0f, 0.0f}
        };

        VB.begin();

        VB.addColor(Color(1,0,0));
        VB.addTexcoord0(vertices[0][2], vertices[0][3]);
        VB.addVertex(vertices[0][0], vertices[0][1], 0);

        VB.addColor(Color(1,0,0));
        VB.addTexcoord0(vertices[1][2], vertices[1][3]);
        VB.addVertex(vertices[1][0], vertices[1][1], 0);

        VB.addColor(Color(1,0,0));
        VB.addTexcoord0(vertices[2][2], vertices[2][3]);
        VB.addVertex(vertices[2][0], vertices[2][1], 0);

        VB.addColor(Color(1,0,0));
        VB.addTexcoord0(vertices[3][2], vertices[3][3]);
        VB.addVertex(vertices[3][0], vertices[3][1], 0);

        VB.addColor(Color(1,0,0));
        VB.addTexcoord0(vertices[4][2], vertices[4][3]);
        VB.addVertex(vertices[4][0], vertices[4][1], 0);

        VB.addColor(Color(1,0,0));
        VB.addTexcoord0(vertices[5][2], vertices[5][3]);
        VB.addVertex(vertices[5][0], vertices[5][1], 0);

        VB.end();

        //Activate vertext Buffer
        VB.activate();
        glDrawArrays(GL_TRIANGLES, 0, 6);
        VB.deactivate();

        x += (ch.Advance >> 6) * scale;
    }

}


bool ShowText::isDead(){
    return dead;
}

void ShowText::update(const std::string& text, float x, float y, float scale, glm::vec3 color) {
    if (!pShader) {
        std::cout << "BaseModel::draw() no shader found" << std::endl;
        return;
    } else {
        this->text = text;
        this->x = x;
        this->y = y;
        this->scale = scale;
        this->color = color;
        dead = true;
    }
}

void ShowText::shader(BaseShader *shader, bool deleteOnDestruction) {
    this->pShader = shader;
}

