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
#include <GLFW/glfw3.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <game/util/GameCamera.h>
#include <framework/shader/PhongShader.h>
#include <game/shader/TerrainShader.h>

#else
#define GLFW_INCLUDE_GLCOREARB
#define GLFW_INCLUDE_GLEXT
#include <glfw/glfw3.h>
#endif


#ifdef WIN32
#define ASSET_DIRECTORY "C:/Users/saeli/Documents/GitHub/computergrafik_hausarbeit/assets/"
#else
#define ASSET_DIRECTORY "../assets/"
#endif


Application::Application(GLFWwindow* pWin) : pWindow(pWin)
{
    // Skybox
    pSkybox = new Model(ASSET_DIRECTORY "models/skybox/skybox.obj", false);
    pSkybox->shader(new PhongShader(), true);
    Models.push_back(pSkybox);

    // Terrain
    pTerrain = new Terrain(ASSET_DIRECTORY, 0.5, 8);
    pTerrain->shader(new TerrainShader(ASSET_DIRECTORY), true);
    Models.push_back(pTerrain);

    // Player Car
    pTank = new Tank(ASSET_DIRECTORY, pTerrain);
    pTank->shader(new PhongShader(ASSET_DIRECTORY), true);
    Models.push_back(pTank);

    // Kamera und KeyManager
    keyManager = new KeyManager(pWindow);
    Cam = new GameCamera(pWin, pTank, pTerrain);

    restart = false;
    printedOnce = false;
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

    // Verhalten im laufenden Spiel
    if (deadTimer < 500) {
        // User Input einlesen
        keyManager->readUserInput(false);

        //Punkte Ausgabe
        if (points < (unsigned int)pTank->getPosition()) {
            std::cout << "Aktuelle Punktzahl: " << this->points << std::endl;
            points = pTank->getPosition();
            this->deadTimer = 0;
        }
        else if (pTank->getPosition() != 0) {
            deadTimer++;
        }
    }
    else {
        if (!printedOnce) {
            std::cout << "Punkte in dieser Runde: " << points << std::endl;
            std::cout << "Druecke die <Leertaste> oder <R> um ein neues Spiel zu starten!"<< std::endl;
            printedOnce = true;
        }
        
        //User Input für die Bewegung des Spielers sperren
        keyManager->readUserInput(true);
        if (keyManager->getRestartKey() == 1) {
            restart = true;
        }
        
    }
   

    // Debug Modus Wechsel
    if(keyManager->getDebugStartKey()) Cam = new Camera(pWindow);
    if(keyManager->getDebugEndKey()) Cam = new GameCamera(pWindow, pTank, pTerrain);


    // Alle Objekte aktualisieren
    Cam->update();
    pTank->update(dTime, keyManager->getForwardKey(), keyManager->getBackwardKey());
    pTerrain->update();
    pSkybox->transform(Matrix().translation(0,pTank->getHeight() - 32,0));
}

void Application::draw()
{
    // 1. clear screen
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // 2. setup shaders and draw models
    for (const auto &model : Models)
        model->draw(*Cam);

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

bool Application::getEndOfGame() {
    return restart;
}