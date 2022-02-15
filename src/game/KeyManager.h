//
// Created by kevin on 12.02.2022.
//

#ifndef COMPUTERGRAFIK_PRAKTIKUM_KEYMANAGER_H
#define COMPUTERGRAFIK_PRAKTIKUM_KEYMANAGER_H


#ifdef WIN32
#include <GL/glew.h>
#include <glfw/glfw3.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <list>

#else
#define GLFW_INCLUDE_GLCOREARB
#define GLFW_INCLUDE_GLEXT
#include <glfw/glfw3.h>
#endif

class KeyManager {
public:
    KeyManager(GLFWwindow* pWindow);
    virtual ~KeyManager();
    void readUserInput();
    float getForwardKey();
    float getBackwardKey();
    float getDebugStartKey();
    float getDebugEndKey();

protected:
    GLFWwindow* pWindow;

    std::list<int> forwardKeys;
    float forwardValue = 0.0;

    std::list<int> backwardKeys;
    float backwardValue = 0.0;

    std::list<int> debugStartKeys;
    float debugStartValue = 0.0;

    std::list<int> debugEndKeys;
    float debugEndValue = 0.0;
};


#endif //COMPUTERGRAFIK_PRAKTIKUM_KEYMANAGER_H
