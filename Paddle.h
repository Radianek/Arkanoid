//
// Created by adm on 19.05.2023.
//

#ifndef PROJEKT_PADDLE_H
#define PROJEKT_PADDLE_H
#include <SFML/Graphics.hpp>

using namespace sf;

class Paddle {
public:
    Paddle(float pos_X, float pos_Y);
    void update();
    const RectangleShape& getShape() const;

    float left();
    float right();
    float top();
    float bottom();

private:

    RectangleShape shape;
    const float paddle_width{120.0f};
    const float paddle_high{20.0f};
    const float paddle_velocity{6.0f};
    Vector2f velocity {paddle_velocity, 0};
    void draw(RenderTarget& target, RenderStates state)const;
};


#endif //PROJEKT_PADDLE_H
