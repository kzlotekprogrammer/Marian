#pragma once

#include <string>
using namespace std;

#include "SFML/Graphics.hpp"

string intToStr(int n);
float B2DtoSF(float n);
float SFtoB2D(float n);

enum
{
	F_PLAYER = 0x0001,
	F_ENEMY = 0x0002,
	F_BULLET = 0x0004,
	F_WALL = 0x0008,
	F_ITEM = 0x0016
};

static sf::Color ID_PLAYER(0, 0, 0);

static sf::Color ID_GHOST_WEAK(230, 230, 230);
static sf::Color ID_GHOST_AVERAGE(210, 210, 210);
static sf::Color ID_GHOST_HARD(190, 190, 190);	

static sf::Color ID_SKELETON_WEAK(150, 150, 150);
static sf::Color ID_SKELETON_AVERAGE(130, 130, 130);
static sf::Color ID_SKELETON_HARD(110, 110, 110);

static sf::Color ID_BAT_WEAK(80, 80, 80);
static sf::Color ID_BAT_AVERAGE(60, 60, 60);
static sf::Color ID_BAT_HARD(40, 40, 40);

static sf::Color ID_EMPTY(255, 255, 255);
static sf::Color ID_RED_BRICK(136, 0, 21);
static sf::Color ID_START(200, 191, 231);
static sf::Color ID_FINISH(163, 73, 164);
static sf::Color ID_LAVA(237, 28, 36);
static sf::Color ID_LAVA_UP(255, 174, 201);
static sf::Color ID_WATER(0, 162, 232);
static sf::Color ID_WATER_UP(153, 217, 234);
static sf::Color ID_GROUND(185, 122, 87);
static sf::Color ID_GRASS_LOW(181, 230, 29);
static sf::Color ID_GRASS_HIGH(34, 177, 76);
static sf::Color ID_WOOD(128, 64, 64);

static sf::Color ID_COIN_1(255, 242, 0);
static sf::Color ID_COIN_2(255, 232, 0);
static sf::Color ID_COIN_3(255, 222, 0);
static sf::Color ID_COIN_4(255, 212, 0);
static sf::Color ID_COIN_5(255, 202, 0); 