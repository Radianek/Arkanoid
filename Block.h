//
// Created by adm on 19.05.2023.
//

#ifndef PROJEKT_BLOCK_H
#define PROJEKT_BLOCK_H
#include <SFML/Graphics.hpp>

class Block {
public:
    Block(float pos_X, float pos_Y, float width, float height); //block constructor
    const sf::RectangleShape& getShape() const;     // function that return block shape
    sf::Vector2f position();        //vector that stores the coordinates of the blocks
    sf::Vector2f size();     //vector that stores the size of the blocks

    float left(); //variable that returns the position of the left edge of the block
    float right();  //variable that returns the position of the right edge of the block
    float top();    //variable that returns the position of the top edge of the block
    float bottom(); //variable that returns the position of the bottom edge of the block

    bool is_destroyed();       //varibale that return destroyed to the block
    void destroy();         //function that change block destroyed value to the true
    void restore();         //function that change block destroyed value to the false
    bool destroyed{false};  // variable that store a block destoryed value
    int points;     //variable that store a points value
    sf::RectangleShape shape;  //object represent a block shape

private:

    void draw(sf::RenderTarget& target, sf::RenderStates state)const; //function that draw a block
};


#endif //PROJEKT_BLOCK_H
