#ifndef PLAYERBALL_H
#define PLAYERBALL_H

#include "customball.h"

class PlayerBall : public CustomBall {
private:
    const sf::RenderWindow * window;
    bool useKeyboard = true;

public:
    PlayerBall(const float & arg_radius,
               const sf::RenderWindow* arg_window, const bool & keyboard);
    void animate(const sf::Time & elapsed) override;
    void setEscapeDirection(const sf::Vector2f & position) override;
    void setTexture(const sf::Texture & texture);  
};

#endif // PLAYERBALL_H
