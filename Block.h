//
// Created by adm on 19.05.2023.
//

#ifndef PROJEKT_BLOCK_H
#define PROJEKT_BLOCK_H
#include <SFML/Graphics.hpp>

using namespace sf;

class Block {
public:
    Block(float pos_X, float pos_Y, float width, float height);
    void update();
    const RectangleShape& getShape() const;
    Vector2f position();
    Vector2f size();

    float left();
    float right();
    float top();
    float bottom();
    bool is_destroyed();
    void destroy();

private:
    RectangleShape shape;
    bool destroyed{0};
    void draw(RenderTarget& target, RenderStates state)const;
};


#endif //PROJEKT_BLOCK_H
