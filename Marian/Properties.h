#pragma once

enum
{
    WALL = 1 << 0,
    PLAYER = 1 << 1,
    ENEMY = 1 << 2,
	BULLET = 1 << 3,
	ITEM = 1 << 4
};

///Contains properties
class Properties
{
    public:
        //type
        unsigned int type;
        //making damage
        bool isDangerous;
        //can be remove
        bool isRemovable;
};