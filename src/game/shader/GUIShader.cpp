/**///
// Created by saeli on 24.02.2022.
//

#include "GUIShader.h"

const char *GVertexShaderCode =
        "#version 400\n"
        "in vec4 VertexPos;"
        "in vec2 VertexTexcoord;"
        "out vec2 Texcoord;"
        "uniform mat4 ModelViewProjMat;"
        "void main()"
        "{"
        "    Texcoord = VertexTexcoord;"
        "    gl_Position = VertexPos;"
        "}";

const char *GFragmentShaderCode =
        "#version 400\n"
        "uniform vec3 Color;"
        "out vec4 FragColor;"
        "void main()"
        "{"
        "    FragColor = vec4(Color,0);"
        "}";

GUIShader::GUIShader() : Col(1.0f,0.0f,0.0f)
{
    ShaderProgram = createShaderProgram(GVertexShaderCode, GFragmentShaderCode );

    ColorLoc = glGetUniformLocation(ShaderProgram, "Color");
    assert(ColorLoc>=0);
    //ModelViewProjLoc  = glGetUniformLocation(ShaderProgram, "ModelViewProjMat");
    //assert(ModelViewProjLoc>=0);
}

void GUIShader::activate(const BaseCamera& Cam) const
{
    BaseShader::activate(Cam);

    glUniform3f(ColorLoc, Col.R, Col.G, Col.B);

}
void GUIShader::color( const Color& c)
{
    Col = c;
}