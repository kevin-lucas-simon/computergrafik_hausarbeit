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

#else
#define GLFW_INCLUDE_GLCOREARB
#define GLFW_INCLUDE_GLEXT
#include <glfw/glfw3.h>
#endif
#include "util/vector.h"
#include "util/Matrix.h"

class GameCamera: public BaseCamera {
public:
    GameCamera(GLFWwindow* pWin);
    virtual ~GameCamera() {};

    virtual Vector position() const;
    Vector target() const;
    Vector up() const;

    void setPosition( const Vector& Pos);
    void setTarget( const Vector& Target);
    void setUp( const Vector& Up);

    void mouseInput( int x, int y, int Button, int State);

    virtual void update();
    virtual const Matrix& getViewMatrix() const;
    virtual const Matrix& getProjectionMatrix() const;
protected:
    void updateMouseInput();

    void pan( float dx, float dy);
    void zoom( float dz);
    void rotate( float x, float y );
    Vector getVSpherePos( float x, float y);
    Vector rotateAxisAngle( Vector v, Vector n, float a);

    Matrix m_ViewMatrix;
    Matrix m_ProjMatrix;
    Vector m_Position;
    Vector m_Target;
    Vector m_Up;
    Vector m_Panning;
    Vector m_Zoom;
    Vector m_Rotation;
    int m_LastMouseX;
    int m_LastMouseY;
    int WindowWidth;
    int WindowHeight;
    GLFWwindow* pWindow;
};


#endif //COMPUTERGRAFIK_PRAKTIKUM_GAMECAMERA_H
