#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <chrono>
#include <thread>
#include "Ball.h"
#include "Paddle.h"
#include "Menu.h"
#include "Block.h"
#include "Explosiveblock.h"
#include "Movingblock.h"

using namespace std;
using namespace sf;

template<class C1, class C2>
bool exist_Collision(C1 &A, C2 &B) {
    return A.right() >= B.left() && A.left() <= B.right()
           && A.bottom() >= B.top() && A.top() <= B.bottom();
} //declaration function that describe collision

bool collision(Paddle &paddle, Ball &ball) {
    if (!exist_Collision(paddle, ball)) {
        return false;
    }
    ball.move_up_ball();


    if (ball.getPosition().x < paddle.get_position().x) {
        ball.move_left_ball();
    } else if (ball.getPosition().x > paddle.get_position().x) {
        ball.move_right_ball();
    }


    return true;
}//declaration function that describe collision between ball and paddle
int score = 0;

Explosiveblock exblock(500, 500, 100, 60);
Movingblock moveblock(500, 325, 100,60);

bool collision(Block &block, Ball &ball) {

    if (!exist_Collision(block, ball)) {
        return false;
    }
    if (!block.destroyed) {
        if (exist_Collision(exblock, ball)) {
            exblock.destroy();
            score = score + 50;
        }

        block.destroy();
        score++;
        float overlap_Left{ball.right() - block.left()};
        float overlap_Right{block.right() - ball.left()};
        float overlap_Top{ball.bottom() - block.top()};
        float overlap_Bottom{block.bottom() - ball.top()};

        bool ball_from_left(abs(overlap_Left) < abs(overlap_Right));
        bool ball_from_top(abs(overlap_Top) < abs(overlap_Bottom));

        float min_overlap_x{ball_from_left ? overlap_Left : overlap_Right};
        float min_overlap_y{ball_from_top ? overlap_Top : overlap_Bottom};

        if (abs(min_overlap_x) < abs(min_overlap_y)) {
            ball_from_left ? ball.move_left_ball() : ball.move_right_ball();
        } else {
            ball_from_top ? ball.move_up_ball() : ball.move_down_ball();
        }

        return true;
    }

}   //declaration function that describe collision between ball and blocks


int main() {


    int menu_options = 1;
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
    RenderWindow window(VideoMode(1650, 1050), "Arcanoid");
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
    std::chrono::milliseconds waiting_time(200);
    unsigned blocks_x{15}, blocks_y{4}, block_width{100}, block_height{60};
    vector<Block> blocks;
    exblock.draw_number();
    for (int i = 0; i < blocks_y; i++) {
        for (int j = 0; j < blocks_x; j++) {
            if (i == exblock.draw_number_y && j == exblock.draw_number_x) {

                exblock.set_position();
                blocks.emplace_back(exblock);
            } else {
                Block block((j + 1) * (block_width + 5), (i + 1) * (block_height + 5), block_width, block_height);
                blocks.emplace_back(block);
            }
        }
    } //block making loop


    while (true) //main loop
    {
        if (menu_options == 1) {
            while (window.isOpen()) {
                while (window.pollEvent(event)) {
                    if (event.type == Event::Closed) {
                        window.close();
                        return 0;
                    }

                    if (event.type == Event::KeyPressed) {
                        if (event.key.code == Keyboard::Up) {
                            menu.move_up();
                        } else if (event.key.code == Keyboard::Down) {
                            menu.move_down();
                        } else if (event.key.code == Keyboard::Return) {
                            if (menu.pressed() == 0) {
                                menu_options = 0;
                            }
                            if (menu.pressed() == 1) {
                                menu_options = 2;
                            }
                            if (menu.pressed() == 2) {
                                menu_options = -1;
                            }
                        }
                    }

                } //loop with mein menu
                window.clear();
                if (menu_options != 1) {
                    break;
                }
                window.draw(photo);
                menu.draw(window);
                window.display();
            }

            if (menu_options == -1) //close game option
            {
                window.close();
                return 0;
            } else if (menu_options == 0) //play game option
            {
                while (menu_options == 0) {
                    while (window.isOpen()) {

                        window.clear(Color::Black);
                        window.pollEvent(event);

                        if (event.type == Event::Closed) {
                            window.close();
                            return 0;
                        }

                        ball.update();
                        paddle.update();
                        moveblock.update();
                        collision(paddle, ball);
                        for (auto &block: blocks) {

                            if (collision(block, ball)) {
                                break;
                            }

                        }

                        auto iterator = remove_if(begin(blocks), end(blocks),
                                                  [](Block &block) { return block.is_destroyed(); });
                        blocks.erase(iterator, end(blocks));


                        if (exblock.destroyed == true) {
                            for (auto &block: blocks) {
                                if ((((block.position().x == (((exblock.draw_number_x + 1) - 1) * 105) &&
                                       block.position().y == ((exblock.draw_number_y + 1) - 1) * 65)))
                                    || (((block.position().x == (((exblock.draw_number_x + 1) + 1) * 105) &&
                                          block.position().y == ((exblock.draw_number_y + 1)) * 65)))
                                    || (((block.position().x == (((exblock.draw_number_x + 1) - 1) * 105) &&
                                          block.position().y == (exblock.draw_number_y + 1) * 65)))
                                    || (((block.position().x == (((exblock.draw_number_x + 1) - 1) * 105) &&
                                          block.position().y == ((exblock.draw_number_y + 1) + 1) * 65)))
                                    || (((block.position().x == (((exblock.draw_number_x + 1)) * 105) &&
                                          block.position().y == ((exblock.draw_number_y + 1) + 1) * 65)))
                                    || (((block.position().x == ((exblock.draw_number_x + 1) * 105) &&
                                          block.position().y == ((exblock.draw_number_y + 1) - 1) * 65)))
                                    || (((block.position().x == (((exblock.draw_number_x + 1) + 1) * 105) &&
                                          block.position().y == ((exblock.draw_number_y + 1) + 1) * 65)))
                                    || (((block.position().x == (((exblock.draw_number_x + 1)) * 105) &&
                                          block.position().y == ((exblock.draw_number_y + 1)) * 65)))
                                    || (((block.position().x == (((exblock.draw_number_x + 1) + 1) * 105) &&
                                          block.position().y == ((exblock.draw_number_y + 1) - 1) * 65)))) {
                                    block.destroy();
                                }
                            }
                        } //loop destroying blocks all around explosive block




                        if (ball.getPosition().y > paddle.top()) {
                            paddle.stop_paddle();
                            ball.under_paddle();
                            moveblock.stop();
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
                            moveblock.stop();
                            paddle.stop_paddle();
                            menu.draw_end_menu(window);
                            if (event.type == Event::KeyPressed) {
                                if (event.key.code == Keyboard::Left) {
                                    menu.move_left();
                                    std::this_thread::sleep_for(waiting_time);
                                } else if (event.key.code == Keyboard::Right) {
                                    menu.move_right();
                                    std::this_thread::sleep_for(waiting_time);
                                } else if (event.key.code == Keyboard::Return) {
                                    if (menu.pressed() == 0) //new game options
                                    {
                                        menu.all_on_white();
                                        ball.reset_ball();
                                        moveblock.move();
                                        for (auto &block: blocks) {
                                            if (!block.destroyed) {
                                                block.destroy();
                                            }
                                        }
                                        exblock.restore();
                                        exblock.restore();
                                        exblock.draw_number();
                                        for (int i = 0; i < blocks_y; i++) {
                                            for (int j = 0; j < blocks_x; j++) {
                                                if (i == exblock.draw_number_y && j == exblock.draw_number_x) {
                                                    exblock.set_position();
                                                    blocks.emplace_back(exblock);
                                                } else {
                                                    Block block((j + 1) * (block_width + 5),
                                                                (i + 1) * (block_height + 5), block_width,
                                                                block_height);
                                                    blocks.emplace_back(block);
                                                }
                                            }
                                        }
                                        score = 0;
                                        break;

                                    }
                                    if (menu.pressed() == 1) //back to menu options
                                    {
                                        score = 0;
                                        menu_options = 1;
                                        menu.all_on_white();
                                        ball.reset_ball();
                                        paddle.reset_paddle();
                                        moveblock.move();
                                        paddle.stop_paddle();
                                        exblock.restore();
                                        for (auto &block: blocks) {
                                            if (!block.destroyed) {
                                                block.destroy();
                                            }
                                        }
                                        exblock.draw_number();
                                        for (int i = 0; i < blocks_y; i++) {
                                            for (int j = 0; j < blocks_x; j++) {
                                                if (i == exblock.draw_number_y && j == exblock.draw_number_x) {
                                                    Explosiveblock exblock((j + 1) * (block_width + 5),
                                                                           (i + 1) * (block_height + 5), block_width,
                                                                           block_height);
                                                    blocks.emplace_back(exblock);
                                                } else {
                                                    Block block((j + 1) * (block_width + 5),
                                                                (i + 1) * (block_height + 5), block_width,
                                                                block_height);
                                                    blocks.emplace_back(block);
                                                }
                                            }
                                        }
                                        break;

                                    }
                                    if (menu.pressed() == 2) {
                                        return 0;
                                    }
                                }
                            }
                            paddle.reset_paddle();

                        }//decision describing what will happen if the ball falls under the paddle
                        paddle.restore_velocity();
                        if (Keyboard::isKeyPressed(Keyboard::P)) {
                            ball.stop_game();
                            moveblock.movingblock_stop_game();
                        }
                        if (ball.is_stopped == true)// decision describing what will happen if we stop the gamep
                        {
                            if (ball.getPosition().y <= paddle.top()) // zapobiega wyświetlaniu pause po zakończeniu gry
                            {

                                paddle.stop_paddle();
                                Font font;
                                moveblock.stopped = true;
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


                        Font font;                                              //display score
                        if (!font.loadFromFile("Bambuchinnox.ttf")) {
                            return -1;
                        }
                        Text score_text("Score: " + to_string(score), font, 20);
                        score_text.setFillColor(Color::White);
                        score_text.setPosition(10.f, 10.f);
                        window.draw(score_text);


                        ball.update();
                        paddle.update();
                        moveblock.update();
                        window.draw(ball.get_shape());
                        window.draw(paddle.get_shape());
                        window.draw(moveblock.get_shape());


                        for (auto &block: blocks) {
                            window.draw(block.get_shape());
                        } //draw a blocks
                        window.display();
                        if (blocks.empty()) {
                            exblock.draw_number();
                            for (int i = 0; i < blocks_y; i++) {
                                for (int j = 0; j < blocks_x; j++) {
                                    if (i == exblock.draw_number_y && j == exblock.draw_number_x) {
                                        Explosiveblock exblock((j + 1) * (block_width + 5),
                                                               (i + 1) * (block_height + 5), block_width, block_height);
                                        blocks.emplace_back(exblock);
                                    } else {
                                        Block block((j + 1) * (block_width + 5), (i + 1) * (block_height + 5),
                                                    block_width, block_height);
                                        blocks.emplace_back(block);
                                    }
                                }
                            }
                        } // function describing what will happen if all blocks are destroyed
                    }
                }

            } else if (menu_options == 2) {
                while (window.isOpen()) {
                    window.clear(Color::Black);
                    window.pollEvent(event);

                    if (event.type == Event::Closed) {
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
                    backButton.setPosition(
                            posX / 5 + instructionSprite.getGlobalBounds().width - 7 * backButton.getSize().x,
                            posY + instructionSprite.getGlobalBounds().height - backButton.getSize().y - 200.f);
                    window.draw(backButton);

                    // Tworzenie tekstu "Back"
                    Font font;
                    if (!font.loadFromFile("Bambuchinnox.ttf")) // Ścieżka do pliku czcionki
                    {
                        return -1;
                    }
                    Text backText("Back", font, 20); // Tekst "Back" z czcionką i rozmiarem 20
                    backText.setFillColor(Color::White);
                    backText.setPosition(backButton.getPosition().x + backButton.getSize().x / 2.f -
                                         backText.getGlobalBounds().width / 2.f,
                                         backButton.getPosition().y + backButton.getSize().y / 3.f -
                                         backText.getGlobalBounds().height / 2.f);
                    window.draw(backText);

                    window.display();

                    if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
                        menu_options = 1; // Przejście do menu głównego po naciśnięciu klawisza Escape
                        break;
                    }

                    if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
                        // Sprawdzenie, czy kliknięcie myszką nastąpiło na przycisku "Back"
                        Vector2f mousePosition = window.mapPixelToCoords(
                                Vector2i(event.mouseButton.x, event.mouseButton.y));

                        if (backButton.getGlobalBounds().contains(mousePosition)) {
                            menu_options = 1; // Przejście do menu głównego po kliknięciu przycisku "Back"
                            break;
                        }
                    }
                }
            } //show instruction option
        }
    }
}

