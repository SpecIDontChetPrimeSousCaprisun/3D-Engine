#ifndef INC_3DENGINE_IMPORTMANAGER_H
#define INC_3DENGINE_IMPORTMANAGER_H

#include <SFML/System/String.hpp>
#include "Mesh.h"

class ImportManager {
public:
    static std::vector<Mesh*> import(sf::String);
};


#endif //INC_3DENGINE_IMPORTMANAGER_H