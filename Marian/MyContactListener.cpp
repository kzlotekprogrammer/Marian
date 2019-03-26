#include "MyContactListener.h"

MyContactListener::MyContactListener()
{
	NextLevel = false;
}

MyContactListener::~MyContactListener()
{

}

void MyContactListener::BeginContact(b2Contact * contact)
{
    Entity * userDataA =(Entity *)contact->GetFixtureA()->GetBody()->GetUserData();
    Entity * userDataB =(Entity *)contact->GetFixtureB()->GetBody()->GetUserData();

    b2Fixture * fixtureA = contact->GetFixtureA();
    b2Fixture * fixtureB = contact->GetFixtureB();

    //player
    for(int i = 0; i < 2; i++)
    {
        if(userDataA->properties.type == PLAYER)
        {
            Player * player =(Player *)userDataA;

            if(userDataB->properties.type == ENEMY)
            {
                if(fixtureA == player->lowerSensorFixture 
					&& fixtureA->GetBody()->GetPosition().y - SFtoB2D(30) > fixtureB->GetBody()->GetPosition().y)
                {
                    if(userDataB->properties.isRemovable == true)
                    {
                        player->bounce();
						userDataB->takeDamage(1);
                    }
                    else
                    {
						player->takeDamage(1);
                    }
                }
                else
                {
                    if(fixtureA == player->fixture)
                    {
                        player->takeDamage(1);
                    }
                }
            }
            else if(userDataB->properties.type == BULLET)
            {

            }
            else if(userDataB->properties.type == WALL)
            {
				if (userDataB->id == ID_FINISH)
				{
					NextLevel = true;
				}
				else if(userDataB->properties.isDangerous == true)
                {
                    player->takeDamage(1000);
                }
                else if(userDataB->properties.isRemovable == true)
                {
                    if(fixtureA == player->upperSensorFixture)
                    {
                        if(player->removingWallClock.getElapsedTime().asSeconds() > 0.2f)
                        {
                            userDataB->takeDamage(1);
                            player->removingWallClock.restart();
                        }
                    }
                }
            }
			else if (userDataB->properties.type == ITEM)
			{
				Item * item = (Item *)userDataB;

				item->Collect(player);
				item->toRemove = true;
			}

            return;
        }

        swap(fixtureA, fixtureB);
        swap(userDataA, userDataB);
    }

    //enemy
    for(int i = 0; i < 2; i++)
    {
        if(userDataA->properties.type == ENEMY)
        {
            if(userDataB->properties.type == BULLET)
            {
                userDataA->takeDamage(1);
                userDataB->takeDamage(1);
            }
			else if (userDataB->properties.type == WALL)
			{
				if (userDataB->properties.isDangerous == true)
				{
					userDataA->takeDamage(1000);
				}
			}

            return;
        }

        swap(fixtureA, fixtureB);
        swap(userDataA, userDataB);
    }

    //bullet
    for(int i = 0; i < 2; i++)
    {
        if(userDataA->properties.type == BULLET)
        {
            if(userDataB->properties.type == WALL)
            {
                if(userDataB->fixture->IsSensor() == true)
                {
                    return;
                }
                if(userDataB->properties.isRemovable == true)
                {
					userDataA->takeDamage(1);
					userDataB->takeDamage(1);
                }
            }

			userDataA->takeDamage(1);
            return;
        }

        swap(fixtureA, fixtureB);
        swap(userDataA, userDataB);
    }
}