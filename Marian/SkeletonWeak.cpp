#include "SkeletonWeak.h"

SkeletonWeak::SkeletonWeak(b2World * t_world, sf::Vector2f t_positionSFML) : Skeleton(t_world, t_positionSFML, 28, 6)
{
    //data
    id = ID_SKELETON_WEAK;
    properties.isRemovable = true;
    maxSpeed = 5;
    health = 1;

    //Box2D body
    body->SetUserData(this);
}

SkeletonWeak::~SkeletonWeak()
{

}
