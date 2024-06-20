#ifndef ENEMYBALL_H
#define ENEMYBALL_H

#include "customball.h"

class EnemyBall : public CustomBall {
private:
    void setRandomDirection();

public:
    EnemyBall(const float & arg_radius,
              const sf::Vector2f & position);
    void animate(const sf::Time & elapsed) override;
    void setEscapeDirection(const sf::Vector2f & position) override;
    void setTexture(const sf::Texture & texture);  
};

#endif // ENEMYBALL_H
