/**///
// Created by saeli on 24.02.2022.
//

#include "GUIShader.h"
#include "../../../libraries/glm/include/detail/type_mat.hpp"
#include "../../../libraries/glm/include/detail/type_mat4x4.hpp"
#include "../../../libraries/glm/include/gtx/orthonormalize.hpp"

const char *GVertexShaderCode =
        "#version 400\n"
        "in vec4 VertexPos;"
        "out vec2 texCoords;"
        "uniform mat4 projection;"
        "void main(){"
        "    gl_Position = VertexPos;"
        "    texCoords = VertexPos.zw;"
        "}";

const char *GFragmentShaderCode =
        "#version 400\n"
        "in vec2 texCoords;"
        "out vec4 color;"
        "uniform sampler2D text;"
        "uniform vec3 texColor;"
        "void main(){"
        "    vec4 sampled = vec4(1.0,1.0,1.0,texture(text,texCoords).r);"
        "    color = vec4(texColor, 1.0) * sampled;"
        "}";



GUIShader::GUIShader() : Col(1.0f, 0.0f, 0.0f)
{
    ShaderProgram = createShaderProgram(GVertexShaderCode, GFragmentShaderCode );

    ColorLoc = glGetUniformLocation(ShaderProgram, "ModelViewProjMat");
}

void GUIShader::activate(const BaseCamera& Cam) const
{
    BaseShader::activate(Cam);
    Matrix ModelViewProj = Cam.getProjectionMatrix() * Cam.getViewMatrix() * modelTransform();
    //glUniformMatrix4fv(ModelViewProjLoc, 1 , GL_FALSE, ModelViewProj.m);

}

void GUIShader::deactivate()  {
    BaseShader::deactivate();
}
void GUIShader::color( const Color& c)
{
    Col = c;
}