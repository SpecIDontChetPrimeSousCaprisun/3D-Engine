#include "Mesh.h"

#include <iostream>

#include "Line.h"

std::vector<Mesh*> Mesh::meshes;

Mesh::Mesh(std::vector<Line*> lines, Vec3* pivot) :
    lines(lines), pivot(pivot) {
    meshes.push_back(this);
}

void Mesh::calculateMovement() {
    for (Line* line : lines) {
        Vec3 rotatedPos1 = line->start;
        Vec3 rotatedPos2 = line->end;

        pivot->x += velocity.x;
        pivot->y += velocity.y;
        pivot->z += velocity.z;

        rotatedPos1.x -= pivot->x;
        rotatedPos1.y -= pivot->y;
        rotatedPos1.z -= pivot->z;

        rotatedPos2.x -= pivot->x;
        rotatedPos2.y -= pivot->y;
        rotatedPos2.z -= pivot->z;

        rotatedPos1.rotateX(angularVelocity.x);
        rotatedPos1.rotateY(angularVelocity.y);
        rotatedPos1.rotateZ(angularVelocity.z);

        rotatedPos2.rotateX(angularVelocity.x);
        rotatedPos2.rotateY(angularVelocity.y);
        rotatedPos2.rotateZ(angularVelocity.z);

        rotatedPos1.x += pivot->x;
        rotatedPos1.y += pivot->y;
        rotatedPos1.z += pivot->z;

        rotatedPos2.x += pivot->x;
        rotatedPos2.y += pivot->y;
        rotatedPos2.z += pivot->z;

        line->start = rotatedPos1;
        line->end = rotatedPos2;
    }
}

void Mesh::calculateAllMeshes() {
    for (Mesh* m : meshes) {
        m->calculateMovement();
    }
}
