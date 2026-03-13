//
// Created by chevre on 2/12/26.
//
#include "Window.h"
#include <SFML/Graphics.hpp>
#include <algorithm>
#include "Line.h"
#include "Mesh.h"
#include <cmath>
#include <iostream>

sf::RenderWindow currentWindow;
Vec3 Window::camPos(0, 0, 0);
Vec3 Window::camRot(0, 0, 0);
bool Window::mouseLocked = true;
bool Window::altWasPressed = true;

void Window::initialize() {
    currentWindow.create(sf::VideoMode({800, 600}), "Title");
    currentWindow.setFramerateLimit(60);
}

void Window::mainLoop() {
    auto size = currentWindow.getSize();
    sf::Vector2i center(size.x / 2, size.y / 2);

    currentWindow.setMouseCursorVisible(false);
    sf::Mouse::setPosition(center, currentWindow);

    while (currentWindow.isOpen()) {
        while (auto event = currentWindow.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                currentWindow.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LAlt)) {
            if (!altWasPressed) {
                mouseLocked = !mouseLocked;
                currentWindow.setMouseCursorVisible(!mouseLocked);
                altWasPressed = true;
            }
        } else {
            altWasPressed = false;
        }

        Mesh::calculateAllMeshes();

        if (mouseLocked) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(currentWindow);
            sf::Vector2i delta = mousePos - center;

            camRot.x = std::clamp(camRot.x - delta.y, -89.0f, 89.0f);
            camRot.y -= delta.x;

            sf::Mouse::setPosition(center, currentWindow);
        }

        float yawRad   = camRot.y * (M_PI / 180.0f);
        float pitchRad = camRot.x * (M_PI / 180.0f);

        std::cout << yawRad << std::endl;

        Vec3 forward(0, 0, 0);

        forward.x = cos(pitchRad) * sin(yawRad);
        forward.y = sin(pitchRad);
        forward.z = cos(pitchRad) * cos(yawRad);

        Vec3* worldUp = new Vec3(0,1,0);

        Vec3 right = *forward.Cross(worldUp); // right-hand cross product

        Vec3 camVel(0, 0, 0);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z)) {
            camVel.x += forward.x;
            camVel.y += forward.y;
            camVel.z += forward.z;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
            camVel.x -= forward.x;
            camVel.y -= forward.y;
            camVel.z -= forward.z;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
            camVel.x += right.x;
            camVel.y += right.y;
            camVel.z += right.z;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) {
            camVel.x -= right.x;
            camVel.y -= right.y;
            camVel.z -= right.z;
        }

        float length = std::sqrt(camVel.x*camVel.x + camVel.y*camVel.y + camVel.z*camVel.z);
        if (length > 0.0f)
        {
            camVel.x /= length;
            camVel.y /= length;
            camVel.z /= length;
        }

        float speed = 1.f;

        camPos.x += camVel.x * speed;
        camPos.y += camVel.y * speed;
        camPos.z += camVel.z * speed;

        currentWindow.clear(sf::Color::Black);
        Line::drawAllLines(currentWindow);
        currentWindow.display();
    }
}
