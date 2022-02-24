//
//  Application.hpp
//  ogl4
//
//  Created by Philipp Lensing on 16.09.16.
//  Copyright © 2016 Philipp Lensing. All rights reserved.
//

#ifndef Application_hpp
#define Application_hpp

#include <stdio.h>
#include <list>
#include <game/terrain/TerrainChunk.h>
#include <game/terrain/Terrain.h>
#include <game/player/Tank.h>
#include <game/util/KeyManager.h>
#include "game/gui/LoosingGUI.h"

class Application
{
public:
    typedef std::list<BaseModel*> ModelList;
    Application(GLFWwindow* pWin);
    ~Application(){}
    void start();
    void update(float dtime);
    void draw();
    void end();
    bool getEndOfGame();
    void restart();

protected:
    BaseCamera* Cam;
    ModelList Models;
    GLFWwindow* pWindow;
    KeyManager* keyManager;

    BaseModel* pSkybox;
    Terrain* pTerrain;
    Tank* pTank;

    LoosingGUI* pLoosingGUI;

    unsigned int points = 0;
    unsigned int deadTimer = 0;
};

#endif /* Application_hpp */
