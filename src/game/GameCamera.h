//
// Created by kevin on 14.02.2022.
//

#ifndef COMPUTERGRAFIK_PRAKTIKUM_GAMECAMERA_H
#define COMPUTERGRAFIK_PRAKTIKUM_GAMECAMERA_H

#include <iostream>
#ifdef WIN32
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <camera/Camera.h>
#include <game/player/PlayerPositionService.h>
#include <game/world/TerrainControlService.h>

#else
#define GLFW_INCLUDE_GLCOREARB
#define GLFW_INCLUDE_GLEXT
#include <glfw/glfw3.h>
#endif
#include "util/vector.h"
#include "util/Matrix.h"
#define _USE_MATH_DEFINES
#include "math.h"

class GameCamera: public BaseCamera {
public:
    GameCamera(GLFWwindow* pWin, PlayerPositionService* player, TerrainControlService* terrain);
    virtual ~GameCamera() {};

    virtual Vector position() const;
    Vector target() const;

    void setPosition( const Vector& Pos);
    void setTarget( const Vector& Target);

    virtual void update();
    virtual const Matrix& getViewMatrix() const;
    virtual const Matrix& getProjectionMatrix() const;
protected:
    Matrix m_ViewMatrix;
    Matrix m_ProjMatrix;
    Vector m_Position;
    Vector m_Target;
    Vector m_Up;
    int WindowWidth;
    int WindowHeight;

    GLFWwindow* pWindow;
    PlayerPositionService* player;
    TerrainControlService* terrain;

    float cameraZoom = MIN_CAM_DEPTH;

    const float MAX_CAM_HEIGHT = 8;
    const float MAX_CAM_DEPTH = 50.0;
    const float MIN_CAM_DEPTH = 5.0;
    const float CAM_ANGLE = M_PI/8;
    const float CAM_SPEED_FACTOR = 30.0;
    const float CAM_ZOOM_SPEED = 0.05;
};


#endif //COMPUTERGRAFIK_PRAKTIKUM_GAMECAMERA_H
