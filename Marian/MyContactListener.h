#pragma once

#include "Box2D/Box2D.h"

//#include "Entity.h"
#include "Player.h"
#include "Item.h"

///Class which manages collisions
class MyContactListener : public b2ContactListener
{
    public:
		///Constructor
        MyContactListener();
		///Destructor
        virtual ~MyContactListener();
		///Called when collision is detected
        virtual void BeginContact(b2Contact * contact);

		bool NextLevel;
    private:
};
