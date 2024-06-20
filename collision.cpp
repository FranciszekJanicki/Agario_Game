#include "collision.h"

bool checkCollision(const CustomBall* ball1, const CustomBall* ball2) {
   float sumRadius = 0.9 * (ball1->getRadius() + ball2->getRadius());
   //ALLOWING FOR A SLIGHT OVERLAPPING OF THE BALLS
   sf::Vector2f diff = ball1->getPosition() - ball2->getPosition();
   float distanceSquared = diff.x * diff.x + diff.y * diff.y;

   if (distanceSquared <= sumRadius * sumRadius) {
       return true;
   }
   else {
       return false;
   }
}

void collision(CustomBall* player,
               std::vector<CustomBall*> & enemies,
               std::vector<CustomBall*> & foods,
               int & score) {

    //SAME SIZE BALLS WILL GO THROUGH EACH OTHER
    for (auto it = enemies.begin(); it != enemies.end();) {
        CustomBall* enemy = *it;
        if (checkCollision(player, enemy)) {
            float enemyRadius = enemy->getRadius();
            float playerRadius = player->getRadius();
            if (playerRadius > enemyRadius) {
                it = enemies.erase(it);
                player->setRadius(sqrt(playerRadius * playerRadius +
                                       enemyRadius * enemyRadius));
                enemy->setDead(true);
                score += enemyRadius;
            }
            else if (player->getRadius() < enemy->getRadius()) {
                enemy->setRadius(sqrt(playerRadius * playerRadius +
                                      enemyRadius * enemyRadius));
                ++it;
                player->setDead(true);
            }
            else {
                ++it;
            }
        }
        else {
            ++it;
        }
    }

    for (auto it = enemies.begin(); it != enemies.end(); ++it) {
        CustomBall* enemy = *it;
        for (auto fIt = foods.begin(); fIt != foods.end();) {
            CustomBall* food = *fIt;
            if (checkCollision(enemy, food)) {
                float foodRadius = food->getRadius();
                float enemyRadius = enemy->getRadius();
                fIt = foods.erase(fIt);
                enemy->setRadius(sqrt(enemyRadius * enemyRadius +
                                      foodRadius * foodRadius));
            }
            else {
                ++fIt;
            }
        }
    }

    for (auto it = foods.begin(); it != foods.end();) {
        CustomBall* food = *it;
        if (checkCollision(player, food)) {
            float foodRadius = food->getRadius();
            float playerRadius = player->getRadius();
            it = foods.erase(it);
            player->setRadius(sqrt(playerRadius * playerRadius +
                                   foodRadius * foodRadius));
             score += foodRadius;
        }
        else {
            ++it;
        }
    }

    for (auto it = enemies.begin(); it != enemies.end(); ++it) {
        CustomBall* enemy1 = *it;
        for (auto it2 = it + 1; it2 != enemies.end();) {
            CustomBall* enemy2 = *it2;
            if (checkCollision(enemy1, enemy2)) {
                float enemy2Radius = enemy2->getRadius();
                float enemy1Radius = enemy1->getRadius();
                if (enemy1Radius > enemy2Radius) {
                    it2 = enemies.erase(it2);
                    enemy1->setRadius(sqrt(enemy1Radius * enemy1Radius +
                                           enemy2Radius * enemy2Radius));
                    enemy2->setDead(true);
                }
                else {
                    it = enemies.erase(it);
                    enemy2->setRadius(sqrt(enemy1Radius * enemy1Radius +
                                           enemy2Radius * enemy2Radius));
                    enemy1->setDead(true);
                    break;
                }
            }
            else {
                ++it2;
            }
        }
    }
}

