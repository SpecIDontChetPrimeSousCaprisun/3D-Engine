#ifndef INC_3DENGINE_WINDOW_H
#define INC_3DENGINE_WINDOW_H

#include <SFML/Graphics.hpp>
#include "Line.h"

class Window {
public:
    static inline sf::RenderWindow currentWindow;
    static Vec3 camPos, camRot;

    static void initialize();
    static void mainLoop();
private:
    static bool mouseLocked, altWasPressed;
};

#endif //INC_3DENGINE_WINDOW_H
