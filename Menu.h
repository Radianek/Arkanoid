//
// Created by adm on 20.05.2023.
//

#ifndef PROJEKT_MENU_H
#define PROJEKT_MENU_H

#include <SFML/Graphics.hpp>

class Menu
{
public:
    sf::Text main_menu[3];   //array containing the main menu
    sf::Text end_menu[3];  // array containing the final menu
    Menu(float width, float  height);  // menu constructor
    void draw(sf::RenderWindow& window);        //function that draw main menu window
    void draw_end_menu(sf::RenderWindow& window);   //funcition that draw end menu window
    void MoveUp();  //function responsible for change slection when press up arrow
    void MoveDown();    //function responsible for change slection when press down arrow
    void MoveLeft();    //function responsible for change slection when press left arrow
    void MoveRight();   //function responsible for change slection when press right arrow
    void all_on_white();    //function responsible change text color on white
    int pressed()       //function that returns the selected options in the menu
    {
        return selected;
    }
    ~Menu();  //menu destructor

private:
    int selected;  //variable specifying the player's current selection
    sf::Font font;  //variable specyfying font

};
#endif