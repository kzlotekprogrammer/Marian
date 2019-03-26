#include "Coin.h"



Coin::Coin(int t_value, b2World * t_world, sf::Vector2f t_positionSFML, int t_rect_x, int t_rect_y) : Item(t_world, t_positionSFML)
{
	//data
	value = t_value;
	properties.type = ITEM;
	properties.isDangerous = false;
	properties.isRemovable = false;

	//Box2D body
	body->SetGravityScale(0);
	body->SetType(b2_dynamicBody);
	body->SetUserData(this);

	//Box2D shape
	b2CircleShape circle;
	circle.m_radius = 0.1f;
	circle.m_p = b2Vec2(SFtoB2D(32), SFtoB2D(-32));

	//Box2D fixture
	b2FixtureDef fixtureDef;
	fixtureDef.filter.categoryBits = F_ITEM;
	fixtureDef.filter.maskBits = F_PLAYER;
	fixtureDef.shape = &circle;
	fixtureDef.friction = 0.0f;
	fixtureDef.density = 1.0f;
	fixture = body->CreateFixture(&fixtureDef);

	rect_y = 47;
	if (value >= 20)
	{
		rect_x = 30;
		id = ID_COIN_5;
	}
	else if (value >= 10)
	{
		rect_x = 28;
		id = ID_COIN_4;
	}
	else if (value >= 5)
	{
		rect_x = 26;
		id = ID_COIN_3;
	}
	else if (value >= 2)
	{
		rect_x = 27;
		id = ID_COIN_2;
	}
	else
	{
		rect_x = 29;
		id = ID_COIN_1;
	}

	sprite.setTextureRect(sf::IntRect(sf::Vector2i(rect_x * 64, rect_y * 64), sf::Vector2i(64, 64)));
}


Coin::~Coin()
{
}

void Coin::Collect(Player * player)
{
	player->coins += value;
}
