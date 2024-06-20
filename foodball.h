#ifndef FOODBALL_H
#define FOODBALL_H

#include "customball.h"

class FoodBall : public CustomBall {
public:
    FoodBall(const float & arg_radius,
             const sf::Vector2f & position);

    void animate(const sf::Time & elapsed) override;
    void setEscapeDirection(const sf::Vector2f & position) override;
};

#endif // FOODBALL_H
