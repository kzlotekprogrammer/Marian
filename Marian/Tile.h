#pragma once

#include "Entity.h"
///Base class for all tiles
class Tile : public Entity
{
    public:
		///Contructor
        Tile(b2World * t_world, sf::Vector2f t_positionSFML, int t_rect_x, int t_rect_y);
		///Destructor
        virtual ~Tile();

		///Updates texture, position on view etc.
        virtual void update();
};

///Represents tile which ends up level
class Finish : public Tile
{
    public:
		///Contructor
        Finish(b2World * t_world, sf::Vector2f t_positionSFML);
};

///Represents start tile
class Start : public Tile
{
    public:
		///Contructor
        Start(b2World * t_world, sf::Vector2f t_positionSFML);
};

///Represents lava
class Lava : public Tile
{
    public:
		///Contructor
        Lava(b2World * t_world, sf::Vector2f t_positionSFML);
};

///Represents top of lava
class Lava_Up : public Tile
{
    public:
		///Contructor
        Lava_Up(b2World * t_world, sf::Vector2f t_positionSFML);
};

///Represents red brick
class RedBrick : public Tile
{
    public:
		///Contructor
        RedBrick(b2World * t_world, sf::Vector2f t_positionSFML);
};

///Represents water
class Water : public Tile
{
    public:
		///Contructor
        Water(b2World * t_world, sf::Vector2f t_positionSFML);
};

///Represents top of water
class Water_Up : public Tile
{
    public:
		///Contructor
        Water_Up(b2World * t_world, sf::Vector2f t_positionSFML);
};

///Represents ground
class Ground : public Tile
{
    public:
		///Contructor
		Ground(b2World * t_world, sf::Vector2f t_positionSFML);
};

///Represents low grass
class Grass_Low : public Tile
{
    public:
		///Contructor
        Grass_Low(b2World * t_world, sf::Vector2f t_positionSFML);
};

///Represents high grass
class Grass_High : public Tile
{
    public:
		///Contructor
        Grass_High(b2World * t_world, sf::Vector2f t_positionSFML);
};

///Represents wood
class Wood : public Tile
{
    public:
		///Contructor
        Wood(b2World * t_world, sf::Vector2f t_positionSFML);
};
