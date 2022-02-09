//
//  TriangleBoxModel.cpp
//  CGXcode
//
//  Created by Philipp Lensing on 10.10.16.
//  Copyright © 2016 Philipp Lensing. All rights reserved.
//

#include "TriangleBoxModel.h"

TriangleBoxModel::TriangleBoxModel(float Width, float Height, float Depth)
{
    // Übergreifende Vertex Struktur erstellen
    Vector vertexes[] = {
            {Width/2, Height/2, Depth/2}, // Vorderseite (0-3)
            {Width/2, -Height/2, Depth/2},
            {-Width/2, Height/2, Depth/2},
            {-Width/2, -Height/2, Depth/2},
            {Width/2, Height/2, -Depth/2}, // Rückseite (4-7)
            {Width/2, -Height/2, -Depth/2},
            {-Width/2, Height/2, -Depth/2},
            {-Width/2, -Height/2, -Depth/2}
    };

    // Faces Aufbau definieren
    struct Face {
            unsigned int vertexIds[4];
            Vector normal;
    };
    Face faces[] = {
            {2,0,1,3, Vector(0,0,1)},   // vorne
            {4,6,7,5, Vector(0,0,-1)},  // hinten
            {6,4,0,2, Vector(0,1,0)},   // oben
            {3,1,5,7, Vector(0,-1,0)},  // unten
            {0,4,5,1, Vector(1,0,0)},   // rechts
            {6,2,3,7, Vector(-1,0,0)},  // links
    };

    // Textur Hilfsstruktur erstellen
    float texturePosition[4][2] = { {0,0}, {1,0}, {1,1}, {0,1} };

    // Durch alle Faces und dessen verknüpfte Vertexes iterieren und diese dem VertexBuffer hinzufügen
	VB.begin();
    for(auto face : faces) {
        for(int i=0; i<4; i++) {
            VB.addNormal(face.normal);
            VB.addTexcoord0(texturePosition[i][0], texturePosition[i][1]);
            VB.addVertex(vertexes[face.vertexIds[i]]);
        }
    }
    VB.end();

    // Indexierung der Vertexes pro Face (Face Leserichtung rechts, Dreieck Leserichtung links)
    IB.begin();
    for (int i=0; i < sizeof(faces)/ sizeof(faces[0]); i++)
        for (auto faceVertexId : {0,2,1,0,3,2})
            IB.addIndex(i*sizeof(faces[0].vertexIds)/ sizeof(faces[0].vertexIds[0]) + faceVertexId);
    IB.end();
}

void TriangleBoxModel::draw(const BaseCamera& Cam)
{
    BaseModel::draw(Cam);

	VB.activate();
    IB.activate();

    glDrawElements(GL_TRIANGLES, IB.indexCount(), IB.indexFormat(), 0);

    IB.deactivate();
    VB.deactivate();
}
