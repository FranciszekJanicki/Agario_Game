#include <SFML/Window.hpp>

#include "playerball.h"
#include "enemyball.h"
#include "foodball.h"
#include "collision.h"

int main() {

    //TEXTURES
    sf::Texture background_texture = loadTexture("textures/background.png");
    background_texture.setRepeated(true);
    sf::Texture player_texture = loadTexture("textures/put.png");
    sf::Texture enemy_texture = loadTexture("textures/uam.png");
    sf::Font font = loadFont("textures/Arial.ttf");

    //WINDOW
    sf::RenderWindow window(sf::VideoMode(sf::VideoMode::getDesktopMode().width,
                            sf::VideoMode::getDesktopMode().height),
                            "Agario_Game", sf::Style::Fullscreen);
    sf::Vector2u size = window.getSize();
    unsigned int width = size.x;
    unsigned int height = size.y;

    //TEXT
    sf::Text text;
    {
        text.setFont(font);
        text.setFillColor(sf::Color::Yellow);
        text.setStyle(sf::Text::Bold);
        text.setCharacterSize(150);
        text.setPosition(0.05 * width, 0.4 * height);
    }

    //BACKGROUND
    sf::Sprite background;
    {
        background.setTexture(background_texture);
        background.setTextureRect(sf::IntRect(0, 0, width, height));
    }

    //PLAYABLE BALL
    CustomBall *player_ball = new PlayerBall(20, &window, false); //true = keyboard steering, false = mouse steering
    {
        player_ball->setSpeed(100, 100);
        player_ball->setBounds(0, width, 0, height);
        player_ball->setTexture(&player_texture);
    }

    //BOT ENEMY BALLS
    std::vector <CustomBall*> enemyBalls;
    {
        for (int i = 0; i < 20; i++) {
            sf::Vector2f position;
            do {
                position = sf::Vector2f(rand() % width, rand() % height);
            } while (std::hypot(position.x - player_ball->getPosition().x,
                                position.y - player_ball->getPosition().y) < 100.0f); //ASSURING THE ENEMY BALLS CANT SPAWN
            //IN 100 PX DISTANCE FROM THE PLAYER BALL
            enemyBalls.emplace_back(new EnemyBall(20, position));
        }

        for (auto & e : enemyBalls) {
            e->setBounds(0, width, 0, height);
            e->setTexture(&enemy_texture);
        }
    }

    //STATIONARY FOOD BALLS
    std::vector <CustomBall*> food_balls;
    {
        for (int i = 0; i < 500; i++) {
            sf::Vector2f position;
            do {
                position = sf::Vector2f(rand() % width, rand() % height);
            } while (std::hypot(position.x - player_ball->getPosition().x,
                                position.y - player_ball->getPosition().y) < 50.0f); //ASSURING THE FOOD BALLS CANT SPAWN
            //IN 50 PX DISTANCE FROM THE PLAYER BALL
            food_balls.emplace_back(new FoodBall(5, position));
        }

        for (auto & f : food_balls) {
            f->setBounds(0, width, 0, height);
            f->setOrigin(f->getRadius(), f->getRadius());
        }
    }

    int score = player_ball->getRadius();
    sf::Clock clock;
    bool game_running = true;

    //MAIN GAME LOOP
    while (window.isOpen() && game_running) {
        sf::Time elapsed = clock.restart();

        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        //LOGIC
        collision(player_ball, enemyBalls, food_balls, score);

        float playerSize = player_ball->getRadius();
        player_ball->setOrigin(playerSize, playerSize);
        player_ball->animate(elapsed);

        //CHANGING DIRECTIONS OF SMALLER BALLS IF BIGGER BALL IS NEARBY (THEY RUN AWAY FROM BIGGER ENEMY)
        for (unsigned int i = 0; i < enemyBalls.size(); i++) {
            float size1 = enemyBalls[i]->getRadius();
            sf::Vector2f position1 = enemyBalls[i]->getPosition();

            for (unsigned int j = i + 1; j < enemyBalls.size(); j++) {
                float size2 = enemyBalls[j]->getRadius();
                sf::Vector2f position2 = enemyBalls[j]->getPosition();
                //CHANGE ENEMY BALL DIRECTION IF BIGGER ENEMY BALL IS NEARBY
                if (size1 > size2) {
                    enemyBalls[j]->setEscapeDirection(position1);
                } else if (size1 < size2) {
                    enemyBalls[i]->setEscapeDirection(position2);
                }
            }

            //CHANGE ENEMY BALL DIRECTION IF BIGGER PLAYER BALL IS NEARBY
            /*if (size1 < playerSize) {
                sf::Vector2f position = player_ball->getPosition();
                enemyBalls[i]->setEscapeDirection(position);
            }*/ //I COMMENTED IT OUT FOR PRESENTATION PURPOSES, ITS CHALLENGING TO WIN WITH IT

            enemyBalls[i]->setOrigin(size1, size1);
            enemyBalls[i]->animate(elapsed);
        }

        //PLAYER IS DEAD
        if (player_ball->allDead()) {
            text.setString("    LOSE!!! SCORE: " + std::to_string(score));
            window.draw(text);
            window.display();
            sf::sleep(sf::seconds(3));
            game_running = false;
        }

        //ENEMIES ARE DEAD
        if (std::all_of(enemyBalls.begin(), enemyBalls.end(),
                        [](CustomBall* ball) {
                             return ball->allDead(); })) {
            text.setString("PUT WINS!!! SCORE: " + std::to_string(score));
            window.draw(text);
            window.display();
            sf::sleep(sf::seconds(3));
            game_running = false;
        }

        window.draw(background);

        for (auto & e : enemyBalls) {
            window.draw(*e);
        }

        for (auto & f : food_balls) {
            window.draw(*f);
        }

        window.draw(*player_ball);

        window.display();
    }

    //DELETING POINTERS
    delete player_ball;

    for (auto & e : enemyBalls) {
        delete e;
    }

    for (auto & f : food_balls) {
        delete f;
    }

    return 0;
}
