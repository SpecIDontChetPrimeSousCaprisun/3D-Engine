#ifndef INC_3DENGINE_MESH_H
#define INC_3DENGINE_MESH_H

#include "Line.h"
#include <vector>

class Mesh {
public:
    Mesh(std::vector<Line*>, Vec3*);
    Vec3 angularVelocity = Vec3(0, 0, 0);
    Vec3 velocity = Vec3(0, 0, 0);

    static void calculateAllMeshes();
private:
    static std::vector<Mesh*> meshes;

    void calculateMovement();

    std::vector<Line*> lines;
    Vec3* pivot;
};

#endif //INC_3DENGINE_MESH_H