#pragma once

#include "Bullet.h"

enum
{
    MS_STOP = 1,
    MS_LEFT = 2,
    MS_RIGHT = 3
};

///Class which represents player
class Player : public Entity
{
    public:
		///Constructor
		Player(b2World * t_world, sf::Vector2f t_positionSFML);
        ///Destructor
		~Player();

		///Updates texture, position on view etc.
        virtual void update();

		///Checks whether player is on ground or not
        bool onGround();
        ///Player will jump
		void jump();
		///Called when player jump on enemy
        void bounce();
        ///Applies left force to player
		void left();
		///Applies right force to player
        void right();
		///Slows down element
		void stop();
		///Creates bullet if it is possible
        Bullet * shoot();
		///Method called when player take damage
		void takeDamage(int damage);

        b2Fixture * upperSensorFixture;
        b2Fixture * lowerSensorFixture;

		sf::Clock removingWallClock;
		sf::Clock takingDamage;

		int coins;
		bool shooting;

    private:
        sf::Clock shootingClock;
        sf::Clock jumpClock;
        sf::Clock animationClock;

        int inJump;
        int directionTexture;
        int nowFrame;
        int moveState;

		///Help to detect if player is in air or on ground etc.
        class MyQueryCallback : public b2QueryCallback
        {
            public:
				///Constructor
                MyQueryCallback(Player * t_player);
				///Called when fixture is found
				virtual bool ReportFixture(b2Fixture * fixture);

                int howMany;
                Player * player;
        };
};
