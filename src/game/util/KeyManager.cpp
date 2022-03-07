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

    // Tasten für Debug Camera
    debugStartKeys.push_back(GLFW_KEY_F3);
    debugEndKeys.push_back(GLFW_KEY_F1);

    //Tasten für Spiel neu starten
    restartGameKeys.push_back(GLFW_KEY_SPACE);
    restartGameKeys.push_back(GLFW_KEY_R);
}

KeyManager::~KeyManager() {}

void KeyManager::readUserInput(bool dead) {
    // Tasten für vorwärtsfahren
    if (!dead) {
        forwardValue = 0;
        for (const auto& key : forwardKeys)
            if (glfwGetKey(pWindow, key) != 0)
                forwardValue = glfwGetKey(pWindow, key);

        // Tasten für rückwärts fahren
        backwardValue = 0;
        for (const auto& key : backwardKeys)
            if (glfwGetKey(pWindow, key) != 0)
                backwardValue = glfwGetKey(pWindow, key);
    }
    else {
        forwardValue = 0;
        backwardValue = 0;
        restartValue = 0;
        for (const auto& key : restartGameKeys)
            if (glfwGetKey(pWindow, key) != 0)
                restartValue = glfwGetKey(pWindow, key);
    }
   
    // Tasten für Debug Modus starten
    debugStartValue = 0;
    for (const auto &key : debugStartKeys)
        if(glfwGetKey(pWindow, key) != 0)
            debugStartValue = glfwGetKey(pWindow, key);

    // Tasten für Debug Modus beenden
    debugEndValue = 0;
    for (const auto &key : debugEndKeys)
        if(glfwGetKey(pWindow, key) != 0)
            debugEndValue = glfwGetKey(pWindow, key);


}

float KeyManager::getForwardKey() {
    return forwardValue;
}

float KeyManager::getBackwardKey() {
    return backwardValue;
}

float KeyManager::getDebugStartKey() {
    return debugStartValue;
}

float KeyManager::getDebugEndKey() {
    return debugEndValue;
}

float KeyManager::getRestartKey() {
    return restartValue;
}