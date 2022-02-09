//
//  LineBoxModel.cpp
//  CGXcode
//
//  Created by Philipp Lensing on 10.10.16.
//  Copyright © 2016 Philipp Lensing. All rights reserved.
//

#include "LineBoxModel.h"

LineBoxModel::LineBoxModel( float Width, float Height, float Depth )
{
	// VertexBuffer öffnen
    VB.begin();

    // Vorderseite
    VB.addVertex(-Width/2, -Height/2, Depth/2);
    VB.addVertex(Width/2, -Height/2, Depth/2);
    VB.addVertex(Width/2, Height/2, Depth/2);
    VB.addVertex(-Width/2, Height/2, Depth/2);

    // Rückseite
    VB.addVertex(-Width/2, -Height/2, -Depth/2);
    VB.addVertex(Width/2, -Height/2, -Depth/2);
    VB.addVertex(Width/2, Height/2, -Depth/2);
    VB.addVertex(-Width/2, Height/2, -Depth/2);

    // Zwischenbereich
    VB.addVertex(-Width/2, -Height/2, Depth/2);
    VB.addVertex(-Width/2, -Height/2, -Depth/2);
    VB.addVertex(Width/2, -Height/2, Depth/2);
    VB.addVertex(Width/2, -Height/2, -Depth/2);
    VB.addVertex(Width/2, Height/2, Depth/2);
    VB.addVertex(Width/2, Height/2, -Depth/2);
    VB.addVertex(-Width/2, Height/2, Depth/2);
    VB.addVertex(-Width/2, Height/2, -Depth/2);

    // Vertexbuffer schließen
    VB.end();
}

void LineBoxModel::draw(const BaseCamera& Cam)
{
    BaseModel::draw(Cam);

    VB.activate();

    // Vorderseite zeichnen
    glDrawArrays(GL_LINE_LOOP, 0, 4);
    // Rückseite zeichnen
    glDrawArrays(GL_LINE_LOOP, 4, 4);
    // Zwischenbereich zeichnen
    glDrawArrays(GL_LINES, 8, 8);

    VB.deactivate();
}
