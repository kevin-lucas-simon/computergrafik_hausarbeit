//
//  Model.cpp
//  ogl4
//
//  Created by Philipp Lensing on 21.09.16.
//  Copyright © 2016 Philipp Lensing. All rights reserved.
//

#include "Model.h"
#include <list>
#include <limits>
#include <iostream>
#include <framework/shader/PhongShader.h>

Model::Model() : pMeshes(NULL), MeshCount(0), pMaterials(NULL), MaterialCount(0)
{

}
Model::Model(const char* ModelFile, bool FitSize) : pMeshes(NULL), MeshCount(0), pMaterials(NULL), MaterialCount(0)
{
    bool ret = load(ModelFile, FitSize);
    if(!ret)
        std::cout << "Could not load model!";
        //throw std::exception();
}
Model::~Model()
{
    if(pMeshes != nullptr)
    	delete[] pMeshes;
    if(pMaterials != nullptr)
        delete[] pMaterials;
    deleteNodes(&RootNode);
}

void Model::deleteNodes(Node* pNode)
{
    if(!pNode)
        return;
    for(unsigned int i=0; i<pNode->ChildCount; ++i)
        deleteNodes(&(pNode->Children[i]));
    if(pNode->ChildCount>0)
        delete [] pNode->Children;
    if(pNode->MeshCount>0)
        delete [] pNode->Meshes;
}

bool Model::load(const char* ModelFile, bool FitSize)
{
    const aiScene* pScene = aiImportFile( ModelFile,aiProcessPreset_TargetRealtime_Fast | aiProcess_TransformUVCoords );

    if(pScene==NULL || pScene->mNumMeshes<=0)
        return false;

    Filepath = ModelFile;
    Path = Filepath;
    size_t pos = Filepath.rfind('/');
    if(pos == std::string::npos)
        pos = Filepath.rfind('\\');
    if(pos !=std::string::npos)
        Path.resize(pos+1);

    loadMeshes(pScene, FitSize);
    loadMaterials(pScene);
    loadNodes(pScene);

    return true;
}

void Model::loadMeshes(const aiScene* pScene, bool FitSize)
{
    // Prüfen, ob die Szene Meshes besitzt
    if(pScene->HasMeshes()) {
        MeshCount = pScene->mNumMeshes;
        pMeshes = new Mesh[MeshCount];

        // Durch alle Meshes iterieren
        for (int meshId = 0; meshId < MeshCount; ++meshId) {
            aiMesh *aMesh = pScene->mMeshes[meshId];

            // Material Eigenschaft
            pMeshes[meshId].MaterialIdx = aMesh->mMaterialIndex;

            // Länge der Bounding Box ermitteln, falls FitSize aktiv ist
            float fitSizeFactor = 1.0f;
            if(FitSize) {
                float diagonalLength = 5.0f; // HIER LÄNGE DEFINIEREN
                // Bounding Box dessen Umwandlungsfaktor ermitteln
                BoundingBox = AABB();
                calcBoundingBox(pScene, BoundingBox);
                fitSizeFactor = diagonalLength/BoundingBox.size().length();
            }

            // Durch Mesh iterieren und einfügen
            pMeshes[meshId].VB.begin();
            pMeshes[meshId].IB.begin();
            int index = 0;
            if(aMesh->HasFaces()) {
                for (int faceId = 0; faceId < aMesh->mNumFaces; ++faceId) {
                    aiFace &aFace = aMesh->mFaces[faceId];

                    // Extrahiere Vertex aus Face
                    for (int i = 0; i < aFace.mNumIndices; ++i) {
                        if (aMesh->HasTextureCoords(0)) {
                            aiVector3D textureCoords = aMesh->mTextureCoords[0][aFace.mIndices[i]];
                            pMeshes[meshId].VB.addTexcoord0(textureCoords.x, 1-textureCoords.y, textureCoords.z);
                        }
                        if (aMesh->HasNormals()) {
                            aiVector3D normal = aMesh->mNormals[aFace.mIndices[i]];
                            pMeshes[meshId].VB.addNormal(normal.x, normal.y, normal.z);
                        }
                        if (aMesh->HasPositions()) {
                            aiVector3D position = aMesh->mVertices[aFace.mIndices[i]];
                            if(FitSize)
                                pMeshes[meshId].VB.addVertex(position.x*fitSizeFactor, position.y*fitSizeFactor,
                                                             position.z*fitSizeFactor);
                            else
                                pMeshes[meshId].VB.addVertex(position.x, position.y, position.z);
                        }
                        pMeshes[meshId].IB.addIndex(index++);
                    }
                }
            }
            pMeshes[meshId].IB.end();
            pMeshes[meshId].VB.end();
        }
    }
}
void Model::loadMaterials(const aiScene* pScene)
{
	MaterialCount = pScene->mNumMaterials;
    pMaterials = new Material[MaterialCount];
    // Durch alle Materialien iterieren
    if(pScene->HasMaterials()) {
        for (unsigned int materialID = 0; materialID < pScene->mNumMaterials; ++materialID) {
            aiMaterial *aMat = pScene->mMaterials[materialID];
            pMaterials[materialID] = Material();

            // Diffuse
            aiColor4D *aDiffuse = new aiColor4D;
            aiGetMaterialColor(aMat, AI_MATKEY_COLOR_DIFFUSE , aDiffuse);
            pMaterials[materialID].DiffColor = Color(aDiffuse->r, aDiffuse->g, aDiffuse->b);

            // Specular
            aiColor4D *aSpecular = new aiColor4D;
            aiGetMaterialColor(aMat, AI_MATKEY_COLOR_SPECULAR , aSpecular);
            pMaterials[materialID].SpecColor = Color(aSpecular->r, aSpecular->g, aSpecular->b);

            // Ambient
            aiColor4D *aAmbient = new aiColor4D;
            aiGetMaterialColor(aMat, AI_MATKEY_COLOR_AMBIENT , aAmbient);
            pMaterials[materialID].AmbColor = Color(aAmbient->r, aAmbient->g, aAmbient->b);

            // Specular Exponent
            aiGetMaterialFloat(aMat, AI_MATKEY_SHININESS, &pMaterials[materialID].SpecExp);

            // Texture
            for (int i = 0; i < aMat->GetTextureCount(aiTextureType_DIFFUSE); ++i) {
                aiString *aTextureName = new aiString;
                aiGetMaterialString(aMat, AI_MATKEY_TEXTURE_DIFFUSE(i), aTextureName);
                std::string file = Path + "/" + aTextureName->data;
                pMaterials[materialID].DiffTex = Texture::LoadShared(file.data());
            }
        }
    }
}
void Model::calcBoundingBox(const aiScene* pScene, AABB& Box)
{
    // Hilfsvariablen erstellen
    float minX = std::numeric_limits<float>::max();
    float minY = std::numeric_limits<float>::max();
    float minZ = std::numeric_limits<float>::max();
    float maxX = std::numeric_limits<float>::min();
    float maxY = std::numeric_limits<float>::min();
    float maxZ = std::numeric_limits<float>::min();

    // Prüfen, ob es Meshes gibt
	if(pScene->HasMeshes()) {
        MeshCount = pScene->mNumMeshes;

        // Durch alle Meshes und dessen Faces iterieren
        for (int meshId = 0; meshId < MeshCount; ++meshId) {
            aiMesh *aMesh = pScene->mMeshes[meshId];
            if(aMesh->HasFaces()) {
                for (int faceId = 0; faceId < aMesh->mNumFaces; ++faceId) {
                    aiFace &aFace = aMesh->mFaces[faceId];
                    for (int i = 0; i < aFace.mNumIndices; ++i) {
                        if (aMesh->HasPositions()) {
                            aiVector3D position = aMesh->mVertices[aFace.mIndices[i]];

                            // Prüfen ob Vertex kleiner als das aktuelle Maximum ist
                            if(position.x < minX)
                                minX = position.x;
                            if(position.y < minY)
                                minY = position.y;
                            if(position.z < minZ)
                                minZ = position.z;

                            // Prüfen ob Vertex größer als das aktuelle Minimum ist
                            if(position.x > maxX)
                                maxX = position.x;
                            if(position.y > maxY)
                                maxY = position.y;
                            if(position.z > maxZ)
                                maxZ = position.z;
                        }
                    }
                }
            }
        }

        // Bounding Box definieren
        Box.Min = Vector(minX, minY, minZ);
        Box.Max = Vector(maxX, maxY, maxZ);
    } else {
        // Leere Bounding Box bei leeren Scenes definieren
        Box.Min = Vector(0, 0, 0);
        Box.Max = Vector(0, 0, 0);
    }
}

void Model::loadNodes(const aiScene* pScene)
{
    deleteNodes(&RootNode);
    copyNodesRecursive(pScene->mRootNode, &RootNode);
}

void Model::copyNodesRecursive(const aiNode* paiNode, Node* pNode)
{
    pNode->Name = paiNode->mName.C_Str();
    pNode->Trans = convert(paiNode->mTransformation);

    if(paiNode->mNumMeshes > 0)
    {
        pNode->MeshCount = paiNode->mNumMeshes;
        pNode->Meshes = new int[pNode->MeshCount];
        for(unsigned int i=0; i<pNode->MeshCount; ++i)
            pNode->Meshes[i] = (int)paiNode->mMeshes[i];
    }

    if(paiNode->mNumChildren <=0)
        return;

    pNode->ChildCount = paiNode->mNumChildren;
    pNode->Children = new Node[pNode->ChildCount];
    for(unsigned int i=0; i<paiNode->mNumChildren; ++i)
    {
        copyNodesRecursive(paiNode->mChildren[i], &(pNode->Children[i]));
        pNode->Children[i].Parent = pNode;
    }
}

void Model::applyMaterial( unsigned int index)
{
    if(index>=MaterialCount)
        return;

    PhongShader* pPhong = dynamic_cast<PhongShader*>(shader());
    if(!pPhong) {
        std::cout << "Model::applyMaterial(): WARNING Invalid shader-type. Please apply PhongShader for rendering models.\n";
        return;
    }

    Material* pMat = &pMaterials[index];
    pPhong->ambientColor(pMat->AmbColor);
    pPhong->diffuseColor(pMat->DiffColor);
    pPhong->specularExp(pMat->SpecExp);
    pPhong->specularColor(pMat->SpecColor);
    pPhong->diffuseTexture(pMat->DiffTex);
}

void Model::draw(const BaseCamera& Cam)
{
    if(!pShader) {
        std::cout << "BaseModel::draw() no shader found" << std::endl;
        return;
    }
    pShader->modelTransform(transform());

    std::list<Node*> DrawNodes;
    DrawNodes.push_back(&RootNode);

    while(!DrawNodes.empty())
    {
        Node* pNode = DrawNodes.front();
        Matrix GlobalTransform;

        if(pNode->Parent != NULL)
            pNode->GlobalTrans = pNode->Parent->GlobalTrans * pNode->Trans;
        else
            pNode->GlobalTrans = transform() * pNode->Trans;

        pShader->modelTransform(pNode->GlobalTrans);

        for(unsigned int i = 0; i<pNode->MeshCount; ++i )
        {
            Mesh& mesh = pMeshes[pNode->Meshes[i]];
            mesh.VB.activate();
            mesh.IB.activate();
            applyMaterial(mesh.MaterialIdx);
            pShader->activate(Cam);
            glDrawElements(GL_TRIANGLES, mesh.IB.indexCount(), mesh.IB.indexFormat(), 0);
            mesh.IB.deactivate();
            mesh.VB.deactivate();
        }
        for(unsigned int i = 0; i<pNode->ChildCount; ++i )
            DrawNodes.push_back(&(pNode->Children[i]));

        DrawNodes.pop_front();
    }
}

Matrix Model::convert(const aiMatrix4x4& m)
{
    return Matrix(m.a1, m.a2, m.a3, m.a4,
                  m.b1, m.b2, m.b3, m.b4,
                  m.c1, m.c2, m.c3, m.c4,
                  m.d1, m.d2, m.d3, m.d4);
}



