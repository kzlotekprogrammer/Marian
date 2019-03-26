#pragma once
#include "Item.h"
///Represents coin
class Coin :
	public Item
{
public:
	///Constructor
	Coin(int value, b2World * t_world, sf::Vector2f t_positionSFML, int t_rect_x = 0, int t_rect_y = 0);
	///Destructor
	virtual ~Coin();

	///Method called when coin is collected
	virtual void Collect(Player * player);
	int value;
};

