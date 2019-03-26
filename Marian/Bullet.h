#pragma once

#include <math.h>

#include "Entity.h"
///Represents bullet
class Bullet : public Entity
{
    public:
		///Constructor
        Bullet(b2World * t_world, sf::Vector2f t_positionSFML, Entity * t_whoIsShooting, float t_maxSpeed);
        ///Destructor
		~Bullet();
		///Updates texture, position on view etc.
        void update();
		///Every method call speeds up bullet, until it reaches max speed
        void move();

    private:
        sf::Clock animationClock;
        sf::Clock movingClock;

        Entity * whoIsShooting;
        float maxSpeed;
        int rect_now;
        int rect_max;
};
