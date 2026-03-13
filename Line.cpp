#include "Line.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "Window.h"
#include <cmath>
#include <algorithm>  // for std::clamp
#include <cstdint>

// x, y: point inside the rectangle
// width, height: size of the rectangle
// c00, c10, c01, c11: colors at top-left, top-right, bottom-left, bottom-right corners
sf::Color getGradientColorAt(float x, float y, float width, float height,
                             const sf::Color& c00, const sf::Color& c10,
                             const sf::Color& c01, const sf::Color& c11)
{
    x = std::clamp(x, 0.f, width);
    y = std::clamp(y, 0.f, height);

    float u = x / width;
    float v = y / height;

    auto lerp = [](float a, float b, float t) { return a + (b - a) * t; };

    std::uint8_t r = static_cast<std::uint8_t>(
        lerp(lerp(c00.r, c10.r, u), lerp(c01.r, c11.r, u), v)
    );
    std::uint8_t g = static_cast<std::uint8_t>(
        lerp(lerp(c00.g, c10.g, u), lerp(c01.g, c11.g, u), v)
    );
    std::uint8_t b = static_cast<std::uint8_t>(
        lerp(lerp(c00.b, c10.b, u), lerp(c01.b, c11.b, u), v)
    );
    std::uint8_t a = static_cast<std::uint8_t>(
        lerp(lerp(c00.a, c10.a, u), lerp(c01.a, c11.a, u), v)
    );

    return sf::Color(r, g, b, a);
}

Vec3::Vec3(int x, int y, int z) : x(x), y(y), z(z) {}

void Vec3::rotateX(float angle) {
    float rads = angle * (M_PI / 180.0);

    float c = std::cos(rads);
    float s = std::sin(rads);

    float oldY = y;
    float oldZ = z;

    y = oldY * c - oldZ * s;
    z = oldY * s + oldZ * c;
}

void Vec3::rotateY(float angle) {
    float rads = angle * (M_PI / 180.0);

    float c = std::cos(rads);
    float s = std::sin(rads);

    float oldX = x;
    float oldZ = z;

    x = oldX * c - oldZ * s;
    z = oldX * s + oldZ * c;
}
void Vec3::rotateZ(float angle) {
    float rads = angle * (M_PI / 180.0);

    float c = std::cos(rads);
    float s = std::sin(rads);

    float oldX = x;
    float oldY = y;

    x = oldX * c - oldY * s;
    y = oldX * s + oldY * c;
}

Vec3 *Vec3::Cross(const Vec3 *b) {
    return new Vec3(
                y * b->z - z * b->y,  // X
                z * b->x - x * b->z,  // Y
                x * b->y - y * b->x   // Z
            );
}

std::vector<Line*> Line::Lines;

Line::Line(const float &x, const float &y, const float &z, const float &x2, const float &y2, const float &z2)
    : start(x, y, z),
      end(x2, y2, z2) {
    Lines.push_back(this);
}

void Line::drawAllLines(sf::RenderWindow &window) {
    for (Line *line: Lines) {
        line->draw(window);
    }
}

void Line::draw(sf::RenderWindow &window) const {
    sf::Color topLeft(255, 0, 0);      // red
    sf::Color topRight(0, 255, 0);     // green
    sf::Color bottomLeft(0, 0, 255);   // blue
    sf::Color bottomRight(255, 255, 0);// yellow

    float width = Window::currentWindow.getSize().x;
    float height = Window::currentWindow.getSize().y;

    LinePoints2 ScreenPoints = getScreenCoordinates();

    sf::Vertex line[] = {
        sf::Vertex(sf::Vector2f(ScreenPoints.start.x, ScreenPoints.start.y),
        getGradientColorAt(ScreenPoints.start.x, ScreenPoints.start.y, width, height,
            topLeft, topRight, bottomLeft, bottomRight)),
        sf::Vertex(sf::Vector2f(ScreenPoints.end.x, ScreenPoints.end.y),
        getGradientColorAt(ScreenPoints.start.x, ScreenPoints.start.y, width, height,
            topLeft, topRight, bottomLeft, bottomRight))
    };

    window.draw(line, 2, sf::PrimitiveType::Lines);
}

LinePoints2 Line::getScreenCoordinates() const {
    auto screenSize = Window::currentWindow.getSize();

    float fov = 90.f; // degrees
    float focalLength = (screenSize.y * 0.5f) / std::tan((fov * 0.5f) * (M_PI / 180.f));

    Vec3 newStart = start;
    Vec3 newEnd   = end;

    // 1️⃣ Translate world relative to camera
    newStart.x -= Window::camPos.x;
    newStart.y -= Window::camPos.y;
    newStart.z -= Window::camPos.z;

    newEnd.x -= Window::camPos.x;
    newEnd.y -= Window::camPos.y;
    newEnd.z -= Window::camPos.z;

    // 2️⃣ Rotate opposite of camera rotation
    newStart.rotateY(-Window::camRot.y);
    newStart.rotateX(-Window::camRot.x);

    newEnd.rotateY(-Window::camRot.y);
    newEnd.rotateX(-Window::camRot.x);

    float near = 0.1f;

    // both behind → reject
    if (newStart.z <= near && newEnd.z <= near)
        return LinePoints2(Vec2(0,0), Vec2(0,0));

    // start behind → clip
    if (newStart.z <= near) {
        float t = (near - newStart.z) / (newEnd.z - newStart.z);

        newStart.x = newStart.x + t * (newEnd.x - newStart.x);
        newStart.y = newStart.y + t * (newEnd.y - newStart.y);
        newStart.z = near;
    }

    // end behind → clip
    if (newEnd.z <= near) {
        float t = (near - newEnd.z) / (newStart.z - newEnd.z);

        newEnd.x = newEnd.x + t * (newStart.x - newEnd.x);
        newEnd.y = newEnd.y + t * (newStart.y - newEnd.y);
        newEnd.z = near;
    }

    // 4️⃣ Perspective divide
    float px1 = (newStart.x / newStart.z) * focalLength;
    float py1 = (newStart.y / newStart.z) * focalLength;

    float px2 = (newEnd.x / newEnd.z) * focalLength;
    float py2 = (newEnd.y / newEnd.z) * focalLength;

    float sx1 = px1 + screenSize.x * 0.5f;
    float sy1 = py1 + screenSize.y * 0.5f;

    float sx2 = px2 + screenSize.x * 0.5f;
    float sy2 = py2 + screenSize.y * 0.5f;

    return LinePoints2(Vec2(sx1, sy1), Vec2(sx2, sy2));
}

