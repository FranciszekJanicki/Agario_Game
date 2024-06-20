#include "foodball.h"

FoodBall::FoodBall(const float & arg_radius,
                   const sf::Vector2f & position):
    CustomBall(arg_radius, position) {
   setRadius(arg_radius);
   setFillColor(sf::Color(rand()%256, rand()%256, rand()%256));
}

void FoodBall::animate([[maybe_unused]]const sf::Time & elapsed) {
}

void FoodBall::setEscapeDirection([[maybe_unused]]const sf::Vector2f & position) {
}

