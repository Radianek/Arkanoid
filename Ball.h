#ifndef BALL_H
#define BALL_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <chrono>
#include <thread>
#include "ICollidable.h"

using namespace sf;

class Ball : public ICollidable{
public:
    Ball(float pos_X, float pos_Y);  // ball constructor
    const CircleShape &get_shape() const;        // function that return ball shape
    void update(); // function that updates the position of the ball and bouncing off the edge
    void move_down_ball(); //function that changes the direction of the ball down
    void move_right_ball();  //function that changes the direction of the ball right
    void move_left_ball();    //function that changes the direction of the ball left
    void move_up_ball();      //function that changes the direction of the ball up
    void under_paddle();    //function that changes ball parameter when the ball is under paddle
    void stop_game();   //function that stop the ball when press P on keyboard
    void reset_ball();  //function that reset the ball
    Vector2f getPosition();  //vector that stores the coordinates of the ball
    float left(); //variable that returns the position of the left edge of the ball
    float right();  //variable that returns the position of the right edge of the ball
    float top();    //variable that returns the position of the top edge of the ball
    float bottom(); //variable that returns the position of the bottom edge of the ball

    float ball_velocity_helper_x;       //variable that stores the velocity of the ball about the x-plane
    float ball_velocity_helper_y;       //variable that stores the velocity of the ball about the y-plane

    bool is_stopped = false;    //variable that use whedn the ball is stopped
    bool ball_under_paddle = false;     //variable that use whedn the ball is under paddle

    Text pause;     //text displayed during pause

    sf::FloatRect get_bounds() const override {
        sf::Vector2f position(/* x */  /* y */);  // Pozycja piłki
        float radius = shape.getRadius();  // Promień piłki

        sf::FloatRect bounds;
        bounds.left = shape.getPosition().x - radius;  // Lewa krawędź granic
        bounds.top = shape.getPosition().y - radius;   // Górna krawędź granic
        bounds.width = 2 * radius;          // Szerokość granic (średnica)
        bounds.height = 2 * radius;         // Wysokość granic (średnica)

        return bounds;  // Zwracanie granic piłki
    }
private:
    CircleShape shape;  //object represent a ball shape
    const float ball_radius{25.0f};  //variable that stores a ball radius
    float ball_velocity{5.0f};       //variable that stores a ball rvelocity
    Vector2f velocity{ball_velocity, ball_velocity};  //vector that stores information about ball velocity
    void draw(RenderTarget &target, RenderStates state) const;  //function that draw a ball

};

#endif
