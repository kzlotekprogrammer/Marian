#include "Tile.h"

#include "Conversion.h"

Tile::Tile(b2World * t_world, sf::Vector2f t_positionSFML, int t_rect_x, int t_rect_y) 
	: Entity(t_world, t_positionSFML, t_rect_x, t_rect_y)
{
    //properties
    properties.type = WALL;

    //Box2D body
    body->SetType(b2_staticBody);

    //Box2D shape
    b2PolygonShape polygon;
    b2Vec2 vertices[4];
    vertices[0] = b2Vec2(SFtoB2D(0), SFtoB2D(0));
    vertices[1] = b2Vec2(SFtoB2D(0), SFtoB2D(-64));
    vertices[2] = b2Vec2(SFtoB2D(64), SFtoB2D(-64));
    vertices[3] = b2Vec2(SFtoB2D(64), SFtoB2D(0));
    polygon.Set(vertices, 4);

    //Box2D fixture
    b2FixtureDef fixtureDef;
    fixtureDef.filter.categoryBits = F_WALL;
    fixtureDef.filter.maskBits = F_BULLET | F_ENEMY | F_PLAYER;
    fixtureDef.shape = &polygon;
    fixtureDef.friction = 0;
    fixtureDef.density = 1;
    fixture = body->CreateFixture(&fixtureDef);
}

Tile::~Tile()
{

}

void Tile::update()
{
    Entity::update();
}

//=============================================

Start::Start(b2World * t_world, sf::Vector2f t_positionSFML) : Tile(t_world, t_positionSFML, 10, 10)
{
    //data
    id = ID_START;
    properties.isDangerous = false;
    properties.isRemovable = false;

    //Box2D body
    body->SetUserData(this);

    //Box2D fixture
    fixture->SetSensor(true);

}

Finish::Finish(b2World * t_world, sf::Vector2f t_positionSFML) : Tile(t_world, t_positionSFML, 11, 10)
{
    //data
    id = ID_FINISH;
    properties.isDangerous = false;
    properties.isRemovable = false;

    //Box2D body
    body->SetUserData(this);

    //Box2D fixture
    fixture->SetSensor(true);
}

Lava::Lava(b2World * t_world, sf::Vector2f t_positionSFML) : Tile(t_world, t_positionSFML, 1, 9)
{
    //data
    id = ID_LAVA;
    properties.isDangerous = true;
    properties.isRemovable = false;

    //Box2D body
    body->SetUserData(this);

    //Box2D fixture
    fixture->SetSensor(true);
}

Lava_Up::Lava_Up(b2World * t_world, sf::Vector2f t_positionSFML) : Tile(t_world, t_positionSFML, 1, 8)
{
    //data
    id = ID_LAVA_UP;
    properties.isDangerous = true;
    properties.isRemovable = false;

    //Box2D body
    body->SetUserData(this);

    //Box2D fixture
    fixture->SetSensor(true);
}

RedBrick::RedBrick(b2World * t_world, sf::Vector2f t_positionSFML) : Tile(t_world, t_positionSFML, 0, 5)
{
    //data
    id = ID_RED_BRICK;
    properties.isDangerous = false;
    properties.isRemovable = false;

    //Box2D body
    body->SetUserData(this);
}

Water::Water(b2World * t_world, sf::Vector2f t_positionSFML) : Tile(t_world, t_positionSFML, 0, 9)
{
    //data
    id = ID_WATER;
    properties.isDangerous = false;
    properties.isRemovable = false;

    //Box2D body
    body->SetUserData(this);

    //Box2D fixture
    fixture->SetSensor(true);
}

Water_Up::Water_Up(b2World * t_world, sf::Vector2f t_positionSFML) : Tile(t_world, t_positionSFML, 0, 8)
{
    //data
    id = ID_WATER_UP;
    properties.isDangerous = false;
    properties.isRemovable = false;

    //Box2D body
    body->SetUserData(this);

    //Box2D fixture
    fixture->SetSensor(true);
}

Ground::Ground(b2World * t_world, sf::Vector2f t_positionSFML) : Tile(t_world, t_positionSFML, 1, 7)
{
    //data
    id = ID_GROUND;
    properties.isDangerous = false;
    properties.isRemovable = true;

    //Box2D body
    body->SetUserData(this);

    //Box2D fixture
    fixture->SetSensor(false);
}

Grass_Low::Grass_Low(b2World * t_world, sf::Vector2f t_positionSFML) : Tile(t_world, t_positionSFML, 1, 41)
{
    //data
    id = ID_GRASS_LOW;
    properties.isDangerous = false;
    properties.isRemovable = false;

    //Box2D body
    body->SetUserData(this);

    //Box2D fixture
    fixture->SetSensor(true);
}

Grass_High::Grass_High(b2World * t_world, sf::Vector2f t_positionSFML) : Tile(t_world, t_positionSFML, 2, 41)
{
    //data
    id = ID_GRASS_HIGH;
    properties.isDangerous = false;
    properties.isRemovable = false;

    //Box2D body
    body->SetUserData(this);

    //Box2D fixture
    fixture->SetSensor(true);
}

Wood::Wood(b2World * t_world, sf::Vector2f t_positionSFML) : Tile(t_world, t_positionSFML, 9, 4)
{
    //data
    id = ID_WOOD;
    properties.isDangerous = false;
    properties.isRemovable = true;

    //Box2D body
    body->SetUserData(this);

    //Box2D fixture
    fixture->SetSensor(false);
}
