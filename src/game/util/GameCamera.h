//
// Created by kevin on 14.02.2022.
//

#ifndef COMPUTERGRAFIK_PRAKTIKUM_GAMECAMERA_H
#define COMPUTERGRAFIK_PRAKTIKUM_GAMECAMERA_H

#include <iostream>
#ifdef WIN32
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <game/player/PlayerPositionService.h>
#include <game/terrain/TerrainControlService.h>
#include <framework/camera/Camera.h>

#else
#define GLFW_INCLUDE_GLCOREARB
#define GLFW_INCLUDE_GLEXT
#include <glfw/glfw3.h>
#endif
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
    float cameraZoom = MIN_CAM_DEPTH;

    GLFWwindow* pWindow;
    PlayerPositionService* player;
    TerrainControlService* terrain;

    // Zoombereich der Kamera bei Geschwindigkeitsänderungen
    const float MIN_CAM_DEPTH = 5.0;
    const float MAX_CAM_DEPTH = 50.0;

    // Winkel der Kamera auf dem Spieler
    const float CAM_ANGLE_ON_PLAYER = M_PI*22.5f/180.0f;
    const float CAM_ANGLE_ON_WORLD = M_PI*65.0f/180.0f;

    // Zoomanpassungsgeschwindigkeit der Kamera im Zusammenhang mit dem Spieler
    const float MIN_PLAYER_SPEED = 0.15;
    const float PLAYER_SPEED_FACTOR = 30.0;
    const float CAM_ZOOM_SPEED_IN = 0.05;
    const float CAM_ZOOM_SPEED_OUT = CAM_ZOOM_SPEED_IN * 2.5;

    // Weltgrößenfaktor, um mögliche Ladedarstellungen zu vermeiden
    const float WORLD_SIZE_FACTOR = 1.2;
};

#endif //COMPUTERGRAFIK_PRAKTIKUM_GAMECAMERA_H
