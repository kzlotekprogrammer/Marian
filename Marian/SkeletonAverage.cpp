#include "SkeletonAverage.h"



SkeletonAverage::SkeletonAverage(b2World * t_world, sf::Vector2f t_positionSFML) : Skeleton(t_world, t_positionSFML, 34, 6)
{    
	//data
	id = ID_SKELETON_WEAK;
	properties.isRemovable = true;
	maxSpeed = 7;
	health = 2;

	//Box2D body
	body->SetUserData(this);
}


SkeletonAverage::~SkeletonAverage()
{
}
