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

    // create LineGrid model with constant color shader
    pModel = new LinePlaneModel(10, 10, 10, 10);
    ConstantShader* pConstShader = new ConstantShader();
    pConstShader->color( Color(1,0,0));
    pModel->shader(pConstShader, true);
    // add to render list
    Models.push_back( pModel );

    // Skybox
    pModel = new Model(ASSET_DIRECTORY "skybox.obj", false);
    pModel->shader(new PhongShader(), true);
    Models.push_back(pModel);

    // TerrainChunk Shader
    pTerrainManager = new Terrain(ASSET_DIRECTORY"colorchess.bmp", 0.25, 24);
    TerrainShader* pTerrainShader = new TerrainShader(ASSET_DIRECTORY);
    pTerrainManager->shader(pTerrainShader, true);
    Models.push_back(pTerrainManager);
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

void Application::update(float dtime)
{
    if(glfwGetKey(pWindow, GLFW_KEY_RIGHT)) {
        pTerrainManager->changeWorldCenter(0.1);
    }
    if(glfwGetKey(pWindow, GLFW_KEY_LEFT)) {
        pTerrainManager->changeWorldCenter(-0.1);
    }

    Cam.update();
}

void Application::draw()
{
    // 1. clear screen
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // 2. setup shaders and draw models
    for( ModelList::iterator it = Models.begin(); it != Models.end(); ++it )
    {
        (*it)->draw(Cam);
    }

    // 3. check once per frame for opengl errors
    GLenum Error = glGetError();
    assert(Error==0);
}
void Application::end()
{
    for( ModelList::iterator it = Models.begin(); it != Models.end(); ++it )
        delete *it;

    Models.clear();
}