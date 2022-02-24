//
// Created by Phileas Scheffer on 23.02.2022.
//

#include "LoosingGUI.h"
#include "framework/model/BaseModel.h"

LoosingGUI::LoosingGUI(const std::string& AssetDirectory){

    this->assetDirectory = assetDirectory;

    VB.begin();

    int Depth = 0;
    int Width =1.5;
    int Height = 1.5;
    // Vorderseite
    VB.addTexcoord0(0,1);
    VB.addVertex(-0.5, -0.5, 0); // Vertex 0
    VB.addTexcoord0(0,0);
    VB.addVertex(0.5, 0.5, 0); // Vertex 1
    VB.addTexcoord0(1,0);
    VB.addVertex(-0.5, 0.5, 0); // Vertex 2
    VB.addTexcoord0(1,1);

    VB.addVertex(0.5, -0.5, 0);// Vertex 3


    // Vertexbuffer schließen

    VB.end();

    IB.begin();

    IB.addIndex(0); //Dreieck 0
    IB.addIndex(1);
    IB.addIndex(2);
    IB.addIndex(0); //Dreieck 1
    IB.addIndex(3);
    IB.addIndex(1);

    IB.end();
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
            IB.activate();
            pShader->activate(Cam);

            std::cout << "DEAD ---------------" << std::endl;
            // Vorderseite zeichnen
            glDrawElements(GL_TRIANGLES, IB.indexCount(), IB.indexFormat(),0);

            VB.deactivate();
            IB.deactivate();
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