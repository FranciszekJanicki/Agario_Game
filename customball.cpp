#include "customball.h"

CustomBall::CustomBall(const float & arg_radius,
                       const sf::Vector2f & position):
    CircleShape(arg_radius) {
   setPosition(position);
}

void CustomBall::setSpeed(const float & v, const float & h) {
    vertical_speed = v;
    horizontal_speed = h;
}

void CustomBall::setBounds(const float & left, const float & right,
                           const float & top, const float & bottom) {
    left_bounds = left;
    right_bounds = right;
    top_bounds = top;
    bottom_bounds = bottom;
}

void CustomBall::setRadius(const float & r) {
    radius = r;

    sf::CircleShape::setRadius(r);
}

float CustomBall::getRadius() const {
    return radius;
}

void CustomBall::bounce() {
    sf::FloatRect bounds= getGlobalBounds();

    if (bounds.left <= left_bounds) {
        horizontal_speed= abs(horizontal_speed);
    }

    if (bounds.left + bounds.width >= right_bounds) {
        horizontal_speed= -abs(horizontal_speed);
    }

    if (bounds.top <= top_bounds) {
        vertical_speed= abs(vertical_speed);
    }

    if (bounds.top + bounds.height >= bottom_bounds) {
         vertical_speed= -abs(vertical_speed);
    }
}

void CustomBall::setDead(const bool & value) {
    is_dead = value;
}

bool CustomBall::allDead() {
    if (is_dead) {
        return true;
    }

    else {
        return false;
    }
}

sf::Texture loadTexture(const std::string & path) {
    sf::Texture texture;
    if (!texture.loadFromFile(path)) {
        std::cerr << "Could not load texture" << std::endl;
    }

    return texture;
}

sf::Font loadFont(const std::string & path) {
    sf::Font font;
    if (!font.loadFromFile(path)) {
       std::cerr << "File Arial.ttf not found !" << std::endl;
    }

    return font;
}


