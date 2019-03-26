#pragma once

#include "Enemy.h"

///Base class for all skeletons
class Skeleton : public Enemy
{
    public:
		///Constructor
        Skeleton(b2World * t_world, sf::Vector2f t_positionSFML, int t_rect_x, int t_rect_y);
        ///Destructor
		virtual ~Skeleton();
		///Updates texture, position on view etc.
        virtual void update();

    private:
        sf::Clock animationClock;

        b2Fixture * sensorFixture[4];

        int firstFrame;
        int nowFrame;
        int maxFrame;

		///Helps detecting walls and holes
        class MyQueryCallback : public b2QueryCallback
        {
            public:
				///Constructor
                MyQueryCallback(Skeleton * skeleton);
				///Called when fixture is found
				virtual bool ReportFixture(b2Fixture * fixture);

                int howMany;
                Skeleton * skeleton;
        };
};