#ifndef COLLISION_H
#define COLLISION_H

#include "playerball.h"
#include "enemyball.h"
#include "foodball.h"

#include <iostream>
#include <vector>

void collision(CustomBall* player,
               std::vector<CustomBall*> & enemies,
               std::vector<CustomBall*> & foods,
               int & score);

#endif // COLLISION_H
