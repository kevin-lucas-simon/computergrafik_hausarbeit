/**///
// Created by saeli on 24.02.2022.
//

#include "GUIShader.h"

const char *GVertexShaderCode =
        "#version 330 core\n"
        "layout (location = 0) in vec4 vertex;"
        "out vec2 texCoords;"
        "uniform mat4 projection;"
        "void main(){"
        "    gl_Position = projection * vec4(vertex.xy, 0.0, 1.0);"
        "    texCoords = vertex.zw;"
        "}";

const char *GFragmentShaderCode =
        "#version 330 core\n"
        "in vec2 texCoords;"
        "out vec4 color;"
        "uniform sampler2D text;"
        "uniform vec3 texColor;"
        "void main(){"
        "    vec4 sampled = vec4(1.0,1.0,1.0,texture(text,texCoords).r);"
        "    color = vec4(texColor, 1.0) * sampled;"
        "}";

GUIShader::GUIShader() : Col(1.0f,0.0f,0.0f)
{
    ShaderProgram = createShaderProgram(GVertexShaderCode, GFragmentShaderCode );

    ColorLoc = glGetUniformLocation(ShaderProgram, "Color");
    //assert(ColorLoc>=0);
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