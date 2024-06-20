#ifndef CUSTOMBALL_H
#define CUSTOMBALL_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <vector>
#include <algorithm>
#include <cmath>
#include <random>
#include <iostream>

class CustomBall : public sf::CircleShape,
        public sf::Texture {
public:
    virtual void animate(const sf::Time & elapsed) = 0;
    virtual void setEscapeDirection(const sf::Vector2f & position) = 0;
    void setSpeed(const float & v, const float & h);
    void setRadius(const float & r);
    float getRadius() const;
    void setDead(const bool & value);
    bool allDead();
    void setBounds(const float & left, const float & right,
                   const float & top, const float & bottom);

protected:
    CustomBall(const float & radius,
               const sf::Vector2f & position);    
    sf::Texture texture;
    bool is_dead = false;
    float radius = 0;
    float horizontal_speed = 0;
    float vertical_speed = 0;
    float left_bounds = 0, right_bounds = 0,
    top_bounds = 0, bottom_bounds = 0;
    void bounce();
};

sf::Texture loadTexture(const std::string & path);

sf::Font loadFont(const std::string & path);

#endif // CUSTOMBALL_H

