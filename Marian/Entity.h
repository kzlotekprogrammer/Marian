#pragma once

#include "SFML/Graphics.hpp"
#include "Box2D/Box2D.h"

#include "Properties.h"
#include "SingletonData.h"

#include "Conversion.h"

///Base class for all elements
class Entity : public sf::Drawable, public sf::Transformable
{
    public:
        ///Constructor
		Entity(b2World * t_world, sf::Vector2f t_positionSFML, int t_rect_x, int t_rect_y);
		///Destructor
		virtual ~Entity();

		///Draws element on view
        virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;
		///Updates texture, position on view etc.
        virtual void update();
		///Entity takes damage
		virtual void takeDamage(int damage);

		///Represents phycial body (contain fixtures)
        b2Body * body;
		///Represents phycial element
        b2Fixture * fixture;
		///Indicates type of element
        sf::Color id;

		///Properties of element
        Properties properties;
		///Indicates, when elemnt should be removed
		bool toRemove;

		///Health of element
		int health;
    protected:
		///Pointer to world, in which element is placed
        b2World * world;

        ///Pointer to texture
        sf::Texture * texture;
		///Represents visual element
        sf::Sprite sprite;

        ///X position in texture
        int rect_x;
		///Y position in texture
        int rect_y;
};
