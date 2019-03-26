#include "SkeletonHard.h"



SkeletonHard::SkeletonHard(b2World * t_world, sf::Vector2f t_positionSFML) : Skeleton(t_world, t_positionSFML, 40, 6)
{
	//data
	id = ID_SKELETON_HARD;
	properties.isRemovable = false;
	maxSpeed = 7;

	//Box2D body
	body->SetUserData(this);
}


SkeletonHard::~SkeletonHard()
{
}
