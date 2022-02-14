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
#include <game/world/TerrainChunk.h>
#include <game/world/Terrain.h>
#include <game/player/Tank.h>
#include <game/KeyManager.h>
#include "camera/camera.h"
#include "shader/phongshader.h"
#include "shader/constantshader.h"
#include "buffer/vertexbuffer.h"
#include "buffer/indexbuffer.h"
#include "model/basemodel.h"

class Application
{
public:
    typedef std::list<BaseModel*> ModelList;
    Application(GLFWwindow* pWin);
    void start();
    void update(float dtime);
    void draw();
    void end();

protected:
    BaseCamera* Cam;
    ModelList Models;
    GLFWwindow* pWindow;
    KeyManager* keyManager;

    // TODO entfernen!
    float worldSizeTest = 32.0;

    Terrain* pTerrain;
    Tank* pTank;
};

#endif /* Application_hpp */
