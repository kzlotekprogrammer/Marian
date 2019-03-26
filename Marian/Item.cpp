#include "Item.h"



Item::Item(b2World * t_world, sf::Vector2f t_positionSFML, int t_rect_x, int t_rect_y) : Entity(t_world, t_positionSFML, t_rect_x, t_rect_y)
{
	properties.type = ITEM;
}


Item::~Item()
{
}
