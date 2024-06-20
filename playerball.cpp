#include "playerball.h"

PlayerBall::PlayerBall(const float & arg_radius,
                       const sf::RenderWindow* arg_window, const bool & keyboard):
    CustomBall(arg_radius, sf::Vector2f(10,10)),
    window(arg_window), useKeyboard(keyboard) {
   setRadius(arg_radius);
}

void PlayerBall::animate(const sf::Time& elapsed) {
    sf::FloatRect circle_bounds = getGlobalBounds();

    if (useKeyboard) {

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            if (circle_bounds.top > top_bounds) {
                move(0, -100*elapsed.asSeconds());
                }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            if (circle_bounds.top + circle_bounds.height < bottom_bounds) {
                move(0, 100*elapsed.asSeconds());
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            if (circle_bounds.left > left_bounds) {
                move(-100 * elapsed.asSeconds(), 0);
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            if (circle_bounds.left + circle_bounds.width < right_bounds) {
                move(100 * elapsed.asSeconds(), 0);
            }
        }
    }

    else {
        sf::Vector2f mousePosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(*window));
        sf::Vector2f direction = mousePosition - getPosition();
        float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

        if (distance > 1.0f) {
            sf::Vector2f velocity = direction / distance * 100.0f * elapsed.asSeconds();
            move(velocity);
        }
    }
}

void PlayerBall::setEscapeDirection([[maybe_unused]]const sf::Vector2f & position) {
}

void PlayerBall::setTexture(const sf::Texture & texture) {
    this->texture = texture;
}
