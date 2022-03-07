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

class Application
{
public:
    typedef std::list<BaseModel*> ModelList;
    Application(GLFWwindow* pWin);
    void start();
    void update(float dtime);
    void draw();
    void end();
    bool getEndOfGame();

protected:
    BaseCamera* Cam;
    ModelList Models;
    GLFWwindow* pWindow;
    KeyManager* keyManager;

    BaseModel* pSkybox;
    Terrain* pTerrain;
    Tank* pTank;

    unsigned int points = 0;
    unsigned int deadTimer = 0;
    bool restart;
    bool printedOnce;
};

#endif /* Application_hpp */
