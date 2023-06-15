//
// Created by adm on 19.05.2023.
//

#ifndef PROJEKT_PADDLE_H
#define PROJEKT_PADDLE_H

#include <SFML/Graphics.hpp>

using namespace sf;

class Paddle {
public:
    Paddle(float pos_X, float pos_Y);       //paddle constructor
    void update();      // function that updates the position of the paddle and bouncing off the edge
    const RectangleShape &get_shape() const;  // function that return paddle shape
    float left(); //variable that returns the position of the left edge of the paddle
    float right();  //variable that returns the position of the right edge of the paddle
    float top();    //variable that returns the position of the top edge of the paddle
    float bottom(); //variable that returns the position of the bottom edge of the paddle
    void restore_velocity(); //function that resotre paddle velocity afetr pause the game
    void stop_paddle();     //function that stop the paddle when press P on keyboard
    void reset_paddle();       //function that reset the paddle
    Vector2f get_position();     //vector that stores the coordinates of the paddle
private:

    RectangleShape shape;       //object represent a paddle shape
    const float paddle_width{130.0f};   //variable that stores a paddle width
    const float paddle_height{20.0f};   //variable that stores a paddle height
    float paddle_velocity{6.0f};        //variable that stores a paddle velocity
    Vector2f velocity{paddle_velocity, 0};     //vector that stores information about paddle velocity
    void draw(RenderTarget &target, RenderStates state) const;      //function that draw a paddle
};


#endif //PROJEKT_PADDLE_H
