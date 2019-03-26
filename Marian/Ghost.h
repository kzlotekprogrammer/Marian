#pragma once

#include "Enemy.h"

///Main class for all ghosts
class Ghost : public Enemy
{
    public:
		///Constructor
        Ghost(b2World * t_world, sf::Vector2f t_positionSFML, int t_rect_x, int t_rect_y);
        ///Destructor
		virtual ~Ghost();
		///Updates texture, position on view etc.
        virtual void update();

    private:
        sf::Clock animationClock;

        b2Fixture * sensorFixture[2];

        int firstFrame;
        int nowFrame;
        int maxFrame;

        ///Helps detecting walls
        class MyQueryCallback : public b2QueryCallback
        {
            public:
				///Constructor
                MyQueryCallback(Ghost * ghost);
				///Called when fixture is found
                virtual bool ReportFixture(b2Fixture * fixture);

                int howMany;
                Ghost * ghost;
        };
};
