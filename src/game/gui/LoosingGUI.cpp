//
// Created by Phileas Scheffer on 23.02.2022.
//

#include "LoosingGUI.h"
#include "framework/model/BaseModel.h"

LoosingGUI::LoosingGUI(){
    VB.begin();

    int Depth = 0;
    int Width =1.5;
    int Height = 1.5;
    // Vorderseite
    VB.addVertex(-0.5, -0.5, 0);
    VB.addVertex(0.5, 0.5, 0);
    VB.addVertex(-0.5, 0.5, 0);

    VB.addVertex(-0.5, -0.5, 0);
    VB.addVertex(0.5, -0.5, 0);
    VB.addVertex(0.5, 0.5, 0);


    //VB.addVertex(-Width / 2, Height / 2, Depth / 2);

    // Vertexbuffer schließen

    VB.end();

}

LoosingGUI::~LoosingGUI() {}

void LoosingGUI::draw(const BaseCamera &Cam) {

    BaseModel::draw(Cam);

    if(!pShader) {
        std::cout << "BaseModel::draw() no shader found" << std::endl;
        return;
    }else{
        if(dead){
            pShader->modelTransform(transform());

            VB.activate();
            std::cout << "DEAD ---------------" << std::endl;
            // Vorderseite zeichnen
            glDrawArrays(GL_TRIANGLES, 0, 3);
            glDrawArrays(GL_TRIANGLES, 3, 3);

            //TODO Was macht das
            pShader->activate(Cam);
            VB.deactivate();
        }
    }

}

bool LoosingGUI::isDead(){
    return dead;
}

void LoosingGUI::update() {
    dead = true;
}

void LoosingGUI::shader(BaseShader *shader, bool deleteOnDestruction) {
    this->pShader = shader;
}