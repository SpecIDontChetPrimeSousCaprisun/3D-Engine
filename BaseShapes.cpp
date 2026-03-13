#include "BaseShapes.h"

#include "Line.h"
#include "Mesh.h"

BaseShapes::BaseShapes() {
    std::vector<Line*> cubeLines;

    cubeLines.push_back(new Line(-50, 50, 100, 50, 50, 100));
    cubeLines.push_back(new Line(50, 50, 100, 50, -50, 100));
    cubeLines.push_back(new Line(50, -50, 100, -50, -50, 100));
    cubeLines.push_back(new Line(-50, -50, 100, -50, 50, 100));

    cubeLines.push_back(new Line(-50, 50, 100, -50, 50, 200));
    cubeLines.push_back(new Line(50, 50, 100, 50, 50, 200));
    cubeLines.push_back(new Line(50, -50, 100, 50, -50, 200));
    cubeLines.push_back(new Line(-50, -50, 100, -50, -50, 200));

    cubeLines.push_back(new Line(-50, 50, 200, 50, 50, 200));
    cubeLines.push_back(new Line(50, 50, 200, 50, -50, 200));
    cubeLines.push_back(new Line(50, -50, 200, -50, -50, 200));
    cubeLines.push_back(new Line(-50, -50, 200, -50, 50, 200));

    Mesh* cube = new Mesh(cubeLines, new Vec3(0, 0, 150));

    std::vector<Line*> prismLines;
    cube->angularVelocity = Vec3(1, 1, 1);

    //Bottom face
    prismLines.push_back(new Line(-50, 50, -100, 50, 50, -100));
    prismLines.push_back(new Line(50, 50, -100, 50, 50, -200));
    prismLines.push_back(new Line(50, 50, -200, -50, 50, -200));
    prismLines.push_back(new Line(-50, 50, -200, -50, 50, -100));

    //Top face
    prismLines.push_back(new Line(-50, 50, -100, 0, -100, -150));
    prismLines.push_back(new Line(50, 50, -100, 0, -100, -150));
    prismLines.push_back(new Line(50, 50, -200, 0, -100, -150));
    prismLines.push_back(new Line(-50, 50, -200, 0, -100, -150));

    Mesh* prism = new Mesh(prismLines, new Vec3(0, 0, -150));

    prism->angularVelocity = Vec3(0, 1, 0);
}
