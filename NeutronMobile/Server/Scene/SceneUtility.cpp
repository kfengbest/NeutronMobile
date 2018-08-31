//
//  SceneUtility.cpp
//  NeutronMobile
//
//  Created by fengka on 8/18/12.
//  Copyright (c) 2012 fengka. All rights reserved.
//

#include "SceneUtility.h"
#include "../Types/Vector3f.h"
#include "../Types/Quaternion.h"
#include "vector"

using namespace Ns::Scene;

Mesh* SceneUtility::createCube()
{
    return NULL;
}


Mesh* SceneUtility::createCone()
{
    Ns::Scene::Mesh* mesh = new Ns::Scene::Mesh(NULL);

    const float coneRadius = 0.5f;
    const float coneHeight = 1.866f;
    const int coneSlices = 40;
    const float dtheta = TwoPi / coneSlices;
    const int vertexCount = coneSlices * 2 + 1;
    const int diskCenterIndex = vertexCount - 1;
    
    int bodyIndexCount = coneSlices * 3;
    int diskIndexCount = coneSlices * 3;
    mesh->bodyIndexCount(bodyIndexCount);
    mesh->diskIndexCount(diskCenterIndex);
    
    std::vector<Vertex> coneVertices = mesh->vertices();
    coneVertices.resize(vertexCount);
    std::vector<Vertex>::iterator vertex = coneVertices.begin();
    
    // Cone's body
    for (float theta = 0; vertex != coneVertices.end() - 1; theta += dtheta) {
        
        // Grayscale gradient
        float brightness = abs(sin(theta));
        vec4 color(brightness, brightness, brightness, 1);
        
        // Apex vertex
        vertex->Position = vec3(0, 1, 0);
        vertex->Color = color;
        vertex++;
        
        // Rim vertex
        vertex->Position.x = coneRadius * cos(theta);
        vertex->Position.y = 1 - coneHeight;
        vertex->Position.z = coneRadius * sin(theta);
        vertex->Color = color;
        vertex++;
    }
    
    // Disk center
    vertex->Position = vec3(0, 1 - coneHeight, 0);
    vertex->Color = vec4(1, 1, 1, 1);
    
    std::vector<unsigned char> coneIndices = mesh->indices();
    coneIndices.resize(bodyIndexCount + diskIndexCount);
    std::vector<unsigned char>::iterator index = coneIndices.begin();
    
    // Body triangles
    for (int i = 0; i < coneSlices * 2; i += 2) {
        *index++ = i;
        *index++ = (i + 1) % (2 * coneSlices);
        *index++ = (i + 3) % (2 * coneSlices);
    }
    
    // Disk triangles
    for (int i = 1; i < coneSlices * 2 + 1; i += 2) {
        *index++ = diskCenterIndex;
        *index++ = i;
        *index++ = (i + 2) % (2 * coneSlices);
    }
    
    return mesh;
}

