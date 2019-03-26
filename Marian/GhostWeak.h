#pragma once

#include "Ghost.h"

///Represents weak type of ghost
class GhostWeak : public Ghost
{
    public:
		///Constructor
        GhostWeak(b2World * t_world, sf::Vector2f t_positionSFML);
		///Destructor
        virtual ~GhostWeak();
};
