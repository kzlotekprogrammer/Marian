#pragma once

#include "Entity.h"

enum
{
    D_LEFT = 1,
    D_RIGHT = 2
};

///Base class for enemies
class Enemy : public Entity
{
    public:
		///Constructor
        Enemy(b2World * t_world, sf::Vector2f t_positionSFML, int t_rect_x, int t_rect_y);
        ///Destructor
		virtual ~Enemy();
		///Updates texture, position on view etc.
        virtual void update();

        int health;
    protected:
		///Updates speed by applying forces
        void move();
		///Changes direction of moving to opposite
        void changeDirection();
		///Enemy takes damage
		void takeDamage(int damage);

		sf::Clock takingDamage;
        sf::Clock directionClock;
        sf::Clock movingClock;

        int directionOfMoving;
        float maxSpeed;
};