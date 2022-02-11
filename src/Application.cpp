//
//  Application.cpp
//  ogl4
//
//  Created by Philipp Lensing on 16.09.16.
//  Copyright © 2016 Philipp Lensing. All rights reserved.
//

#include "Application.h"
#ifdef WIN32
#include <GL/glew.h>
#include <glfw/glfw3.h>
#define _USE_MATH_DEFINES
#include <math.h>
#else
#define GLFW_INCLUDE_GLCOREARB
#define GLFW_INCLUDE_GLEXT
#include <glfw/glfw3.h>
#endif
#include "model/lineplanemodel.h"
#include "model/model.h"
#include "shader/terrainshader.h"


#ifdef WIN32
#define ASSET_DIRECTORY "../assets/"
#else
#define ASSET_DIRECTORY "../assets/"
#endif


Application::Application(GLFWwindow* pWin) : pWindow(pWin), Cam(pWin)
{
    BaseModel* pModel;

    // Skybox
    pModel = new Model(ASSET_DIRECTORY "skybox.obj", false);
    pModel->shader(new PhongShader(), true);
    Models.push_back(pModel);

    // Terrain
    pTerrain = new Terrain(ASSET_DIRECTORY"grass.bmp", 0.5, 12);
    pTerrain->shader(new TerrainShader(ASSET_DIRECTORY), true);
    Models.push_back(pTerrain);

    // Player Car
    pTank = new Tank();
    pTank->bindToTerrain(pTerrain);
    pTank->shader(new PhongShader(ASSET_DIRECTORY), true);
    pTank->loadModels(ASSET_DIRECTORY "tank_bottom.dae", ASSET_DIRECTORY "tank_top.dae");
    Models.push_back(pTank);
}
void Application::start()
{
    glEnable (GL_DEPTH_TEST); // enable depth-testing
    glDepthFunc (GL_LESS); // depth-testing interprets a smaller value as "closer"
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glEnable(GL_BLEND);
//    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Application::update(float dTime)
{
    // User Input Variablen
    int keyFrontBack = 0;

    // User Inputs einlesen
    if(glfwGetKey(pWindow, GLFW_KEY_D) != 0|| glfwGetKey(pWindow, GLFW_KEY_A) != 0) {
        keyFrontBack = glfwGetKey(pWindow, GLFW_KEY_D) - glfwGetKey(pWindow, GLFW_KEY_A);
    }

    // Alle Objekte aktualisieren
    Cam.update();
    pTank->update(dTime, keyFrontBack);
}

void Application::draw()
{
    // 1. clear screen
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // 2. setup shaders and draw models
    for (const auto &model : Models)
        model->draw(Cam);

    // 3. check once per frame for opengl errors
    GLenum Error = glGetError();
    assert(Error==0);
}
void Application::end()
{
    for (const auto model : Models)
        delete model;
    Models.clear();
}