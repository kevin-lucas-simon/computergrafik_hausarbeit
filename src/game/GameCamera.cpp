//
// Created by kevin on 14.02.2022.
//

#include "GameCamera.h"

GameCamera::GameCamera(GLFWwindow* pWin, PlayerPositionService* playerPositionService) : m_Position(0.0f,5.0f,5.0f), m_Target(0.0f,0.0f,0.0f), m_Up(0.0f,1.0f,0.0f), WindowWidth(640), WindowHeight(480), pWindow(pWin)
{
    if(pWindow)
        glfwGetWindowSize(pWindow, &WindowWidth, &WindowHeight);

    m_ViewMatrix.identity();
    m_ProjMatrix.perspective((float)M_PI*65.0f/180.0f, (float)WindowWidth/(float)WindowHeight, 0.045f, 1000.0f);

    this->player = playerPositionService;
}

Vector GameCamera::position() const
{
    return m_Position;
}

Vector GameCamera::target() const
{
    return m_Target;
}

void GameCamera::setPosition( const Vector& Pos)
{
    m_Position = Pos;
}

void GameCamera::setTarget( const Vector& Target)
{
    m_Target = Target;
}

const Matrix& GameCamera::getViewMatrix() const
{
    return m_ViewMatrix;
}

const Matrix& GameCamera::getProjectionMatrix() const
{
    return m_ProjMatrix;
}

void GameCamera::update()
{
    // Langsames Anpassen des Kamerazooms
    if(cameraZoom < MIN_CAM_DEPTH + player->getSpeed() * CAM_SPEED_FACTOR)
        cameraZoom += CAM_ZOOM_SPEED;
    else
        cameraZoom -= CAM_ZOOM_SPEED;

    // Grenzen des Kamerazooms beachten
    if(cameraZoom > MAX_CAM_DEPTH) cameraZoom = MAX_CAM_DEPTH;
    if(cameraZoom < MIN_CAM_DEPTH) cameraZoom = MIN_CAM_DEPTH;

    // Kamerahöhe einstellen
    float cameraHeight = player->getHeight();
    if (cameraHeight > MAX_CAM_HEIGHT) cameraHeight = MAX_CAM_HEIGHT;

    // Kameraposition übergeben und Spieler Fahrzeug als Ziel angeben
    setPosition(Vector(0,cameraHeight,0) + (Vector(0, sin(CAM_ANGLE), cos(CAM_ANGLE)) * cameraZoom));
    setTarget(Vector(0,player->getHeight(),0));


    Vector Pos = position(); //m_Position + m_Panning + m_Zoom + m_Rotation;
    Vector Target = target(); //m_Target + m_Panning;
    m_ViewMatrix.lookAt(Target, m_Up, Pos);
}