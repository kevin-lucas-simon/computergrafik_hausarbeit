//
// Created by kevin on 12.02.2022.
//

#include "KeyManager.h"

KeyManager::KeyManager(GLFWwindow* pWindow) {
    this->pWindow = pWindow;

    // Tasten für vorwärtsfahren
    forwardKeys.push_back(GLFW_KEY_D);
    forwardKeys.push_back(GLFW_KEY_W);
    forwardKeys.push_back(GLFW_KEY_RIGHT);
    forwardKeys.push_back(GLFW_KEY_UP);

    // Tasten für rückwärts fahren
    backwardKeys.push_back(GLFW_KEY_A);
    backwardKeys.push_back(GLFW_KEY_S);
    backwardKeys.push_back(GLFW_KEY_LEFT);
    backwardKeys.push_back(GLFW_KEY_DOWN);
}

KeyManager::~KeyManager() {}

void KeyManager::readUserInput() {
    // Tasten für vorwärtsfahren
    forwardValue = 0;
    for (const auto &key : forwardKeys)
        if(glfwGetKey(pWindow, key) != 0)
            forwardValue = glfwGetKey(pWindow, key);

    // Tasten für rückwärts fahren
    backwardValue = 0;
    for (const auto &key : backwardKeys)
        if(glfwGetKey(pWindow, key) != 0)
            backwardValue = glfwGetKey(pWindow, key);
}

float KeyManager::getForwardKey() {
    return forwardValue;
}

float KeyManager::getBackwardKey() {
    return backwardValue;
}