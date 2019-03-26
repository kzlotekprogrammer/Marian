#include "Entity.h"

Entity::Entity(b2World * t_world, sf::Vector2f t_positionSFML, int t_rect_x, int t_rect_y)
{
    //data
    world = t_world;
    rect_x = t_rect_x;
    rect_y = t_rect_y;

    //singleton data
    texture = SingletonData::getSingletonData().getTexture();
    if(!(SingletonData::getSingletonData().isGood()))
    {
        toRemove = true;
        return;
    }
    toRemove = false;

    //Box2d body
    b2BodyDef bodyDef;
    bodyDef.fixedRotation = true;
    body = world->CreateBody(&bodyDef);
    body->SetTransform(b2Vec2(SFtoB2D(t_positionSFML.x), SFtoB2D(-t_positionSFML.y)), body->GetAngle());
	body->SetUserData(this);

    //SFML sprite
    sprite.setTexture(*texture);
    sprite.setPosition(t_positionSFML);
    sprite.setTextureRect(sf::IntRect(sf::Vector2i(rect_x * 64, rect_y * 64), sf::Vector2i(64, 64)));

	health = 1;
}

Entity::~Entity()
{
    world->DestroyBody(body);
}

void Entity::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(sprite);
}

void Entity::update()
{
    sprite.setPosition(sf::Vector2f(B2DtoSF(body->GetPosition().x), -B2DtoSF(body->GetPosition().y)));
}

void Entity::takeDamage(int damage)
{
	if (properties.isRemovable)
	{
		health -= damage;
		if (health <= 0)
		{
			toRemove = true;
		}
	}
}
