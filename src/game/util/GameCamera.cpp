//
// Created by kevin on 14.02.2022.
//

#include "GameCamera.h"

GameCamera::GameCamera(GLFWwindow* pWin, PlayerPositionService* player, TerrainControlService* terrain) : m_Position(0.0f,5.0f,5.0f), m_Target(0.0f,0.0f,0.0f), m_Up(0.0f,1.0f,0.0f), WindowWidth(640), WindowHeight(480), pWindow(pWin)
{
    if(pWindow)
        glfwGetWindowSize(pWindow, &WindowWidth, &WindowHeight);

    m_ViewMatrix.identity();
    m_ProjMatrix.perspective(CAM_ANGLE_ON_WORLD, (float)WindowWidth/(float)WindowHeight, 0.045f, 1000.0f);

    this->player = player;
    this->terrain = terrain;
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
    if(cameraZoom < MIN_CAM_DEPTH + player->getSpeed() * PLAYER_SPEED_FACTOR && player->getSpeed() > MIN_PLAYER_SPEED)
        cameraZoom += CAM_ZOOM_SPEED_OUT;
    else
        cameraZoom -= CAM_ZOOM_SPEED_IN;

    // Grenzen des Kamerazooms beachten
    if(cameraZoom > MAX_CAM_DEPTH) cameraZoom = MAX_CAM_DEPTH;
    if(cameraZoom < MIN_CAM_DEPTH) cameraZoom = MIN_CAM_DEPTH;


    // Spieler als Kameraziel angeben
    Vector camHeight = Vector(0, player->getHeight(), 0);
    setTarget(camHeight);

    // Kamerawinkel mit Geschwindigkeitszoom berechnen
    setPosition(camHeight + (Vector(0, sin(CAM_ANGLE_ON_PLAYER), cos(CAM_ANGLE_ON_PLAYER)) * cameraZoom));

    // Weltgröße aktualisieren, sodass nur Chunks geladen werden, die tatsächlich sichtbar sind
    terrain->setWorldSize(tan(CAM_ANGLE_ON_WORLD) * cameraZoom * WORLD_SIZE_FACTOR);

    // Kamerawerte berechnen
    Vector Pos = position(); //m_Position
    Vector Target = target(); //m_Target
    m_ViewMatrix.lookAt(Target, m_Up, Pos);
}