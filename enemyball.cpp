#include "enemyball.h"

EnemyBall::EnemyBall(const float & arg_radius, const sf::Vector2f & position):
    CustomBall(arg_radius, position) {
    setRadius(arg_radius);
    setRandomDirection();
    setFillColor(sf::Color(rand()%256, rand()%256, rand()%256));
}

void EnemyBall::setRandomDirection() {
    float angle = static_cast<float>(rand()) /
            static_cast<float>(RAND_MAX) * 2 * 3.1415926f;

    float x = std::cos(angle) * 100;
    float y = std::sin(angle) * 100;

    horizontal_speed = x;
    vertical_speed = y;
}

void EnemyBall::setEscapeDirection(const sf::Vector2f & position) {
    sf::Vector2f currentPosition = getPosition();
    sf::Vector2f direction = currentPosition - position;
    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (distance < 100) {
        sf::Vector2f escapeDirection = direction / distance;
        horizontal_speed = escapeDirection.x * 100;
        vertical_speed = escapeDirection.y * 100;
    }

    bounce();
}

void EnemyBall::animate(const sf::Time & elapsed) {
    move(horizontal_speed * elapsed.asSeconds(),
        vertical_speed * elapsed.asSeconds());

    bounce();
}

void EnemyBall::setTexture(const sf::Texture & texture) {
    this->texture = texture;
}
