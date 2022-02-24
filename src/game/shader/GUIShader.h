//
// Created by saeli on 24.02.2022.
//

#include "framework/shader/BaseShader.h"

#ifndef COMPUTERGRAFIK_PRAKTIKUM_GUISHADER_H
#define COMPUTERGRAFIK_PRAKTIKUM_GUISHADER_H

#endif //COMPUTERGRAFIK_PRAKTIKUM_GUISHADER_H


class GUIShader: public BaseShader
{
public:
    GUIShader();
    void color( const Color& c);
    const Color& color() const { return Col; }
    virtual void activate(const BaseCamera& Cam) const;
private:
    Color Col;
    GLuint ShaderProgram;
    GLint ColorLoc;
    GLint GUILoc;
    GLint GUITex;

};