#ifndef INC_3DENGINE_LINE_H
#define INC_3DENGINE_LINE_H

#include <SFML/Graphics.hpp>
#include <vector>

struct Vec2 {
    float x;
    float y;
};

struct Vec3 {
    float x;
    float y;
    float z;

    Vec3(int x, int y, int z);

    void rotateX(float angle);
    void rotateY(float angle);
    void rotateZ(float angle);
    Vec3* Cross(const Vec3* other);
};

struct LinePoints2 {
    Vec2 start;
    Vec2 end;
};

class Line {
public:
    Line(const float& x, const float& y, const float& z, const float& x2, const float& y2, const float& z2);
    void draw(sf::RenderWindow& window) const;

    static void drawAllLines(sf::RenderWindow& window);
    Vec3 start, end;
private:
    static std::vector<Line*> Lines;

    LinePoints2 getScreenCoordinates() const;
};

#endif //INC_3DENGINE_LINE_H
