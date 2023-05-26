#ifndef BALL_H
#define BALL_H
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

using namespace sf;

class Ball{
public:
    Ball(float pos_X, float pos_Y);

    // Pobierania kształtu piłki
    const CircleShape& getShape() const;
    void update();
    void moveUp();
    void moveDown();
    void moveRight();
    void moveLeft();
    void under_paddle();
    void stop_game();
    void reset_ball();
    Vector2f getPosition();
    // zmiennne zwracające współrzędne krawędzi piłki(pomocne przy kolizjach)
    float left();
    float right();
    float top();
    float bottom();

    float ball_velocity_helper_x;
    float ball_velocity_helper_y;

    bool is_stopped = false;
    bool ball_under_paddle = false;

    Text pause;
private:
    // Obiekt CircleShape reprezentujący kształt piłki
    CircleShape shape;

    const float ball_radius{25.0f};
    float ball_velocity{5.0f};
    Vector2f velocity {ball_velocity, ball_velocity};
    void draw(RenderTarget& target, RenderStates state)const;
};

#endif
