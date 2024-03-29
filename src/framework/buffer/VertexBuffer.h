//
//  VertexBuffer.hpp
//  ogl4
//
//  Created by Philipp Lensing on 19.09.16.
//  Copyright © 2016 Philipp Lensing. All rights reserved.
//

#ifndef VertexBuffer_hpp
#define VertexBuffer_hpp
#ifdef WIN32
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#else
#define GLFW_INCLUDE_GLCOREARB
#define GLFW_INCLUDE_GLEXT
#include <glfw/glfw3.h>
#endif
#include <iostream>
#include <vector>
#include <stdio.h>
#include <framework/util/vector.h>
#include <framework/texture/color.h>

class VertexBuffer
{
public:
    struct Texcoord
    {
        Texcoord() {}
        Texcoord(float _s, float _t, float _u=0) : s(_s), t(_t), u(_u) {}
        float s;
        float t;
        float u;
    };
    
    VertexBuffer();
    ~VertexBuffer();
    
    void begin();
    void addNormal( float x, float y, float z);
    void addNormal( const Vector& v);
    void addColor( const Color& c);
    void addTexcoord0( float s, float t, float u=0.0f );
    void addTexcoord1( float s, float t, float u=0.0f );
    void addTexcoord2( float s, float t, float u=0.0f );
    void addTexcoord3( float s, float t, float u=0.0f );
    void addVertex( float x, float y, float z);
    void addVertex( const Vector& v);
    void end();
    
    void activate();
    void deactivate();
    
    unsigned int vertexCount() { return VertexCount; }
    
    const std::vector<Vector>& vertices() { return Vertices; }
    const std::vector<Vector>& normals() { return Vertices; }
    const std::vector<Color>& colors() { return Colors; }
    const std::vector<Vector>& texcoord0() { return Texcoord0; }
    const std::vector<Vector>& texcoord1() { return Texcoord1; }
    const std::vector<Vector>& texcoord2() { return Texcoord2; }
    const std::vector<Vector>& texcoord3() { return Texcoord3; }

private:

    
    enum ATTRIBUTES
    {
        VERTEX  = 1<<0,
        NORMAL  = 1<<1,
        COLOR   = 1<<2,
        TEXCOORD0 = 1<<3,
        TEXCOORD1 = 1<<4,
        TEXCOORD2 = 1<<5,
        TEXCOORD3 = 1<<6,
    };
    std::vector<Vector> Vertices;
    std::vector<Vector> Normals;
    std::vector<Color> Colors;
    std::vector<Vector> Texcoord0;
    std::vector<Vector> Texcoord1;
    std::vector<Vector> Texcoord2;
    std::vector<Vector> Texcoord3;
    unsigned int ActiveAttributes;
    bool WithinBeginBlock;
    GLuint VBO;
    GLuint VAO;
    bool BuffersInitialized;
    unsigned int VertexCount;
    
    
};

#endif /* VertexBuffer_hpp */
