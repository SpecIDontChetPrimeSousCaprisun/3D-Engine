//
// Created by chevre on 2/13/26.
//

#include "ImportManager.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <SFML/System/String.hpp>
#include <iostream>

#include "Line.h"
#include "Mesh.h"

std::vector<Mesh*> ImportManager::import(sf::String path) {
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(
        path,
        aiProcess_Triangulate | aiProcess_FlipUVs
    );

    if (!scene) {
        std::cerr << importer.GetErrorString() << "\n";
    }

    std::vector<Mesh*> Meshes;

    for (unsigned int i = 0; i < scene->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[i];
        std::vector<Line*> Lines;

        for (unsigned int f = 0; f < mesh->mNumFaces; f++)
        {
            aiFace face = mesh->mFaces[f];

            unsigned int i0 = face.mIndices[0];
            unsigned int i1 = face.mIndices[1];
            unsigned int i2 = face.mIndices[2];

            aiVector3D v0 = mesh->mVertices[i0];
            aiVector3D v1 = mesh->mVertices[i1];
            aiVector3D v2 = mesh->mVertices[i2];

            // Create 3 lines for wireframe
            Lines.push_back(new Line(v0.x, -v0.y, v0.z + 5, v1.x, -v1.y, v1.z + 5));
            Lines.push_back(new Line(v1.x, -v1.y, v1.z + 5, v2.x, -v2.y, v2.z + 5));
            Lines.push_back(new Line(v2.x, -v2.y, v2.z + 5, v0.x, -v0.y, v0.z + 5));
        }

        Mesh* newMesh = new Mesh(Lines, new Vec3(0, 0, 5));

        Meshes.push_back(newMesh);
    }

    return Meshes;
}