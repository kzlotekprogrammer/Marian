#pragma once
#include "Skeleton.h"
///Represents average type of skeleton
class SkeletonAverage :	public Skeleton
{
public:
	///Constructor
	SkeletonAverage(b2World * t_world, sf::Vector2f t_positionSFML);
	///Destructor
	virtual ~SkeletonAverage();
};

