#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Ball.h"
#include "Paddle.h"
#include "Menu.h"
#include "Block.h"

using namespace std;
using namespace sf;

template <class C1, class C2> bool exist_Collision(C1& A, C2& B)
{
     return A.right() >= B.left() && A.left() <= B.right()
     && A.bottom() >= B.top() && A.top() <= B.bottom();
}

bool collision(Paddle& paddle, Ball& ball)
{
    if(!exist_Collision(paddle, ball))
    {
        return false;
    }

    ball.moveUp();

    if(ball.getPosition().x < paddle.getPosition().x)
    {
        ball.moveLeft();
    }
    else if (ball.getPosition().x > paddle.getPosition().x)
    {
        ball.moveRight();
    }


    return true;
}
int score = 0;
bool collision(Block& block, Ball& ball)
{
    if(!exist_Collision(block, ball))
    {
        return false;
    }

    block.destroy();
    score ++;
    float overlap_Left { ball.right() - block.left()};
    float overlap_Right { block.right() - ball.left()};
    float overlap_Top {ball.bottom() - block.top()};
    float overlap_Bottom {block.bottom() - ball.top()};

    bool ball_from_left( abs(overlap_Left) < abs(overlap_Right));
    bool ball_from_top( abs(overlap_Top) < abs(overlap_Bottom));

    float min_overlap_x {ball_from_left ? overlap_Left : overlap_Right};
    float min_overlap_y {ball_from_top ? overlap_Top : overlap_Bottom};

    if(abs(min_overlap_x) < abs(min_overlap_y))
    {
        ball_from_left ? ball.moveLeft() : ball.moveRight();
    }
    else
    {
        ball_from_top ? ball.moveUp() : ball.moveDown();
    }


    return true;
}


int main()
{


    int menu_options =1;
    /***************************************************************
     *          menu_options           *          Function         *
     * ____________________________________________________________*
     *            -1                   *         close             *
     *             0                   *         Game              *
     *             1                   *         MainMenu          *
     *             2                   *         instructions      *
     *             3                   *                           *
     ***************************************************************
     */

    Ball ball(500, 500);
    Paddle paddle(950, 950);
    RenderWindow window (VideoMode(1650, 1050),"Arcanoid");
    Menu menu(1920, 1080);
    Texture mainmenu_photo;
    Texture instruction_photo;
    instruction_photo.loadFromFile("instrukcja.png");
    mainmenu_photo.loadFromFile("obraz.png");
    Sprite photo;
    Text endgame;
    photo.setTexture(mainmenu_photo);
    window.setFramerateLimit(60);
    Event event;
    unsigned blocks_x {15}, blocks_y{4}, block_width{100}, block_height{60};

    vector<Block> blocks;
    for(int i = 0; i< blocks_y;i++)
    {
        for(int j= 0; j < blocks_x; j++)
        {
            blocks.emplace_back((j+1)*(block_width+5),(i+1)*(block_height+5), block_width, block_height);
        }
    }

    while(true)
    {
        if(menu_options ==1)
        {
            while(window.isOpen())
            {
                while (window.pollEvent(event))
                {
                    if(event.type==Event::Closed)
                    {
                        window.close();
                        return 0;
                    }

                    if(event.type==Event::KeyPressed)
                    {
                        if(event.key.code == Keyboard::Up)
                        {
                            menu.MoveUp();
                        }
                        else if(event.key.code == Keyboard::Down)
                        {
                            menu.MoveDown();
                        }
                        else if(event.key.code==Keyboard::Return)
                        {
                            if(menu.pressed()==0)
                            {
                                menu_options=0;
                            }
                            if(menu.pressed()==1)
                            {
                                menu_options=2;
                            }
                            if(menu.pressed()==2)
                            {
                               menu_options=-1;
                            }
                        }
                    }


                }
                window.clear();
                if(menu_options != 1)
                {
                    break;
                }
                window.draw(photo);
                menu.draw(window);
                window.display();
            }

            if(menu_options == -1)
            {
                window.close();
                break;
            }
            else if(menu_options == 0)
            {
                while(menu_options == 0)
                {
                    while (window.isOpen())
                    {

                        window.clear(Color::Black);
                        window.pollEvent(event);

                        if (event.type == Event::Closed) {
                            window.close();
                            return 0;
                        }

                        ball.update();
                        paddle.update();
                        collision(paddle, ball);
                        for (auto &block: blocks)
                        {
                            if (collision(block, ball))
                            {
                                break;
                            }
                        }

                        auto iterator = remove_if(begin(blocks), end(blocks),
                                                  [](Block &block) { return block.is_destroyed(); });
                        blocks.erase(iterator, end(blocks));

                        if (ball.getPosition().y > paddle.top())
                        {
                            ball.under_paddle();
                            Font font;
                            if (!font.loadFromFile("Bambuchinnox.ttf")) {
                                return -1;
                            }
                            Text endgame("THE END", font, 100);
                            endgame.setFillColor(Color::White);
                            endgame.setPosition(window.getSize().x / 2.f - endgame.getGlobalBounds().width / 2.f,
                                                window.getSize().y / 2.f - endgame.getGlobalBounds().height / 2.f -
                                                15.f);
                            window.draw(endgame);
                            //wyświetlanie punktów;
                            Text score_text("Total Score: " + to_string(score), font, 60);
                            score_text.setFillColor(Color::White);
                            score_text.setPosition(window.getSize().x / 2.f - score_text.getGlobalBounds().width / 2.f,
                                                   window.getSize().y / 2.f + endgame.getGlobalBounds().height / 2.f +
                                                   score_text.getGlobalBounds().height / 2.f);
                            window.draw(score_text);
                            paddle.stop_paddle();
                            menu.draw_end_menu(window);
                            if (event.type == Event::KeyPressed) {
                                if (event.key.code == Keyboard::Left) {
                                    menu.MoveLeft();
                                } else if (event.key.code == Keyboard::Right) {
                                    menu.MoveRight();
                                } else if (event.key.code == Keyboard::Return) {
                                    if (menu.pressed() == 0) //new game
                                    {

                                        menu.all_on_white();
                                        ball.reset_ball();
                                        paddle.reset_paddle();
                                        for (auto &block: blocks) {
                                            if(block.destroyed == false) {
                                                block.destroy();
                                            }
                                        }
                                        for(int i = 0; i< blocks_y;i++)
                                        {
                                            for(int j= 0; j < blocks_x; j++)
                                            {
                                                blocks.emplace_back((j+1)*(block_width+5),(i+1)*(block_height+5), block_width, block_height);
                                            }
                                        }
                                        score =0;
                                        break;
                                    }
                                    if (menu.pressed() == 1) //back to menu
                                    {
                                        score =0;
                                        menu_options = 1;
                                        menu.all_on_white();
                                        ball.reset_ball();
                                        paddle.reset_paddle();
                                        for (auto &block: blocks) {
                                            if(block.destroyed == false) {
                                                block.destroy();
                                            }
                                        }
                                        for(int i = 0; i< blocks_y;i++)
                                        {
                                            for(int j= 0; j < blocks_x; j++)
                                            {
                                                blocks.emplace_back((j+1)*(block_width+5),(i+1)*(block_height+5), block_width, block_height);
                                            }
                                        }
                                        break;
                                    }
                                    if (menu.pressed() == 2) //close game
                                    {
                                        window.close();
                                        return 0;
                                    }
                                }
                            }

                        }

                        ball.stop_game();
                        if (ball.is_stopped == true) {
                            if (ball.getPosition().y <= paddle.top()) // zapobiega wyświetlaniu pause po zakończeniu gry
                            {
                                paddle.stop_paddle();
                                Font font;
                                if (!font.loadFromFile("Bambuchinnox.ttf")) {
                                    return -1;
                                }
                                Text pause("PAUSE", font, 100);
                                pause.setFillColor(Color::White);
                                pause.setPosition(1650 / 2.f - pause.getGlobalBounds().width / 2.f,
                                                  1050 / 2.f - pause.getGlobalBounds().height / 2.f);
                                window.draw(pause);
                            }

                        }
                        //Wyświetlanie bieżącego wyniku gracza
                        Font font;
                        if (!font.loadFromFile("Bambuchinnox.ttf")) {
                            return -1;
                        }
                        Text score_text("Score: " + to_string(score), font, 20);
                        score_text.setFillColor(Color::White);
                        score_text.setPosition(10.f, 10.f);
                        window.draw(score_text);


                        ball.update();
                        paddle.update();
                        window.draw(ball.getShape());
                        window.draw(paddle.getShape());

                        for (auto &block: blocks)
                        {
                                window.draw(block.getShape());
                        }
                        window.display();
                        if (blocks.empty())
                        {
                            for(int i = 0; i< blocks_y;i++)
                            {
                                for(int j= 0; j < blocks_x; j++)
                                {
                                    blocks.emplace_back((j+1)*(block_width+5),(i+1)*(block_height+5), block_width, block_height);
                                }
                            }
                        }
                    }
                }
            }
            else if (menu_options == 2)
            {
                while (window.isOpen())
                {
                    window.clear(Color::Black);
                    window.pollEvent(event);

                    if (event.type == Event::Closed)
                    {
                        window.close();
                        return 0;
                    }

                    // Rysowanie obrazka instrukcji
                    Sprite instructionSprite(instruction_photo);

                    // Ustawienie pozycji na środku okna
                    float posX = (window.getSize().x - instructionSprite.getGlobalBounds().width) / 2.f;
                    float posY = (window.getSize().y - instructionSprite.getGlobalBounds().height) / 2.f;
                    instructionSprite.setPosition(posX, posY);

                    window.draw(instructionSprite);

                    // Rysowanie przycisku "Back"
                    RectangleShape backButton(Vector2f(100.f, 40.f));
                    backButton.setFillColor(Color::Red);
                    backButton.setPosition(posX/5 + instructionSprite.getGlobalBounds().width - 7*backButton.getSize().x, posY + instructionSprite.getGlobalBounds().height - backButton.getSize().y - 200.f);
                    window.draw(backButton);

                    // Tworzenie tekstu "Back"
                    Font font;
                    if (!font.loadFromFile("Bambuchinnox.ttf")) // Ścieżka do pliku czcionki
                    {
                        return -1;
                    }
                    Text backText("Back", font, 20); // Tekst "Back" z czcionką i rozmiarem 20
                    backText.setFillColor(Color::White);
                    backText.setPosition(backButton.getPosition().x + backButton.getSize().x / 2.f - backText.getGlobalBounds().width / 2.f, backButton.getPosition().y + backButton.getSize().y / 3.f - backText.getGlobalBounds().height / 2.f);
                    window.draw(backText);

                    window.display();

                    if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
                    {
                        menu_options = 1; // Przejście do menu głównego po naciśnięciu klawisza Escape
                        break;
                    }

                    if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left)
                    {
                        // Sprawdzenie, czy kliknięcie myszką nastąpiło na przycisku "Back"
                        Vector2f mousePosition = window.mapPixelToCoords(Vector2i(event.mouseButton.x, event.mouseButton.y));

                        if (backButton.getGlobalBounds().contains(mousePosition))
                        {
                            menu_options = 1; // Przejście do menu głównego po kliknięciu przycisku "Back"
                            break;
                        }
                    }
                }
            }
        }
    }
}

