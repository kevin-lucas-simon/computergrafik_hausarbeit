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

ShowText::ShowText(const std::string& text, float x, float y, float scale, glm::vec3 color) {

    struct Character {
        unsigned int TextureID; // ID handle of the glyph texture
        glm::vec2 Size;      // Size of glyph
        glm::ivec2 Bearing;   // Offset from baseline to left/top of glyph
        unsigned int Advance;   // Horizontal offset to advance to next glyph
    };

    std::map<GLchar, Character> Characters;

    VB.begin();

    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++) {

        Character ch = Characters[*c];

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

        VB.addVertex(vertices[0][1], vertices[0][2], 0);
        VB.addTexcoord0(vertices[0][3], vertices[0][4]);

        VB.addVertex(vertices[1][1], vertices[1][2], 0);
        VB.addTexcoord0(vertices[1][3], vertices[1][4]);

        VB.addVertex(vertices[2][1], vertices[2][2], 0);
        VB.addTexcoord0(vertices[2][3], vertices[2][4]);

        VB.addVertex(vertices[3][1], vertices[3][2], 0);
        VB.addTexcoord0(vertices[3][3], vertices[3][4]);

        VB.addVertex(vertices[4][1], vertices[4][2], 0);
        VB.addTexcoord0(vertices[4][3], vertices[4][4]);

        VB.addVertex(vertices[5][1], vertices[5][2], 0);
        VB.addTexcoord0(vertices[5][3], vertices[5][4]);

        // Vertexbuffer schließen

        VB.end();

        IB.begin();

        IB.end();
    }
}

ShowText::~ShowText(){

};

void ShowText::draw(const BaseCamera &Cam) {
    BaseModel::draw(Cam);

    if(!pShader) {
        std::cout << "BaseModel::draw() no shader found" << std::endl;
        return;
    }else{
        if(dead){
            pShader->modelTransform(transform());

            VB.activate();
            IB.activate();
            pShader->activate(Cam);
            // Vorderseite zeichnen
            glDrawArrays(GL_TRIANGLES, 0, 6);

            VB.deactivate();
            IB.deactivate();
        }
    }

}

bool ShowText::isDead(){
    return dead;
}

void ShowText::update() {
    dead = true;
}

void ShowText::shader(BaseShader *shader, bool deleteOnDestruction) {
    this->pShader = shader;
}
