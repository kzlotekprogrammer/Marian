#include "GhostWeak.h"

GhostWeak::GhostWeak(b2World * t_world, sf::Vector2f t_positionSFML) : Ghost(t_world, t_positionSFML, 27, 7)
{
    //data
    id = ID_GHOST_WEAK;
    properties.isRemovable = true;
    maxSpeed = 5;
    health = 1;

    //Box2D
    body->SetUserData(this);
}

GhostWeak::~GhostWeak()
{

}
