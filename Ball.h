#ifndef BALL_H
#define BALL_H
#include <SFML/Graphics.hpp>

using namespace sf;

class Ball{
public:
    Ball(float pos_X, float pos_Y);

    // Pobierania kształtu piłki
    const CircleShape& getShape() const;
    void update();

    // zmiennne zwracające współrzędne krawędzi piłki(pomocne przy kolizjach)
    float left();
    float right();
    float top();
    float bottom();

private:
    // Obiekt CircleShape reprezentujący kształt piłki
    CircleShape shape;

    const float ball_radius{10.0f};
    const float ball_velocity{3.0f};
    Vector2f velocity {ball_velocity, ball_velocity};
    void draw(RenderTarget& target, RenderStates state)const;
};

#endif
