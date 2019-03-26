#pragma once
#include "Entity.h"
#include "Player.h"

///Base class for all items
class Item : public Entity
{
public:
	///Constructor
	Item(b2World * t_world, sf::Vector2f t_positionSFML, int t_rect_x = 0, int t_rect_y = 0);
	///Destructor
	virtual ~Item();

	///Called when item is collected
	virtual void Collect(Player * player) = 0;
};

