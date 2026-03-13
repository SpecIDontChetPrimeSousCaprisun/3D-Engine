#include "Window.h"
#include "Line.h"
#include "Mesh.h"
#include "ImportManager.h"
#include <iostream>

#include "BaseShapes.h"

int main(int argc, char** argv) {
    if (argc == 2) {
        std::vector<Mesh*> meshes = ImportManager::import(argv[1]);

        for (Mesh* mesh : meshes) {
            mesh->angularVelocity = Vec3(0, 1, 0);
        }
    } else {
        new BaseShapes();
    }

    Window::initialize();
    Window::mainLoop();

    return 0;
}
