#pragma once

#include "Skeleton.h"
///Represents hard type of skeleton
class SkeletonHard : public Skeleton
{
	public:
		///Constructor
		SkeletonHard(b2World * t_world, sf::Vector2f t_positionSFML);
		///Destructor
		virtual ~SkeletonHard();
};

