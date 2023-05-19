#ifndef BALL_H
#define BALL_H
#include <SFML/Graphics.hpp>

using namespace sf;

class Ball{
public:
    Ball(float pos_X, float pos_Y);
    const CircleShape& getShape() const;// Metoda do pobierania kształtu piłki
private:
    CircleShape shape; // Obiekt CircleShape reprezentujący kształt piłki
    const float ball_radius{10.0f};
    void draw(RenderTarget& target, RenderStates state)const;
};

#endif
