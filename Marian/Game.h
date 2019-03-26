#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <list>
#include <set>

using namespace std;

#include "SFML/Graphics.hpp"
#include "Box2D/Box2D.h"

#include "Player.h"
#include "SkeletonWeak.h"
#include "GhostWeak.h"
#include "SkeletonAverage.h"
#include "SkeletonHard.h"
#include "Coin.h"

#include "Tile.h"

#include "MyContactListener.h"

enum
{
    MENU = 1,
    RESUME = 2,
    NEW_GAME = 3,
    SELECT_LEVEL = 4,
    INSTRUCTION = 5,
    QUIT = 6,
    END = 7
};

///Main class, which contains everything and manages all game
class Game
{
    public:
		///Constructor
        Game();
		///Destructor
        virtual ~Game();
		///Contains main loop of the game
        void run();

    private:
		///Contains loop which manages main menu
        void displayMenu();
		///Contains loop which manages selecting levels
		void displaySelectLevel();
		///Manages submenu which displays instruction
		void displayInstruction();
		///Loads level n
        void loadData(int n);
		///Removes all loaded data of level
        void removeData();
		///Starts or resumes level
        void play();

        //SFML
        sf::RenderWindow window;
        sf::Font font;

        //Box2D
        b2World world;
        MyContactListener myContactListener;

        //data
        Player * player;
		list<b2Body *> DynamicEntitites;
        //list<Entity *> entities;
        bool isLoaded;
		int level;
        unsigned int STATE;
		///Finds elements, which should be displayed on screen
		class MyQueryCallback : public b2QueryCallback
		{
		public:
			int Type;
			set<b2Body*> FoundBodies;
			///Called when fixture is found
			bool ReportFixture(b2Fixture * fixture)
			{
				if (((Entity *)fixture->GetBody()->GetUserData())->properties.type & Type)
				{
					FoundBodies.insert(fixture->GetBody());
				}
				return true;
			}
		};
};