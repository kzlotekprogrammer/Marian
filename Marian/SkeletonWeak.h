#pragma once

#include "Skeleton.h"
///Represents weak type of skeleton
class SkeletonWeak : public Skeleton
{
    public:
		///Constructor
        SkeletonWeak(b2World * t_world, sf::Vector2f t_positionSFML);
		///Destructor
        ~SkeletonWeak();
};
