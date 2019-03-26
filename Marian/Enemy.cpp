#include "Enemy.h"

Enemy::Enemy(b2World * t_world, sf::Vector2f t_positionSFML, int t_rect_x, int t_rect_y) : Entity(t_world, t_positionSFML, t_rect_x, t_rect_y)
{
    properties.isDangerous = true;
    directionOfMoving = D_RIGHT;
    properties.type = ENEMY;

    //Box2D body
    body->SetType(b2_dynamicBody);
}

Enemy::~Enemy()
{

}

void Enemy::update()
{
    Entity::update();
}

void Enemy::move()
{
	float dt = min(movingClock.restart().asSeconds(), 1.0f / 60);

    if(directionOfMoving == D_LEFT)
    {
        if(body->GetLinearVelocity().x > -maxSpeed)
        {
            float force = -50*dt/(1.0f/60);
            body->ApplyForce(b2Vec2(force, 0), body->GetWorldCenter(), true);
        }
    }
    else
    {
        if(body->GetLinearVelocity().x < maxSpeed)
        {
            float force = 50*dt/(1.0f/60);
            body->ApplyForce(b2Vec2(force, 0), body->GetWorldCenter(), true);
        }
    }
}

void Enemy::changeDirection()
{
    if(directionClock.getElapsedTime().asSeconds() > 0.2f)
    {
        if(directionOfMoving == D_LEFT)
            directionOfMoving = D_RIGHT;
        else
            directionOfMoving = D_LEFT;

        directionClock.restart();
    }
}

void Enemy::takeDamage(int damage)
{
	if (damage == 1000)
	{
		health = 0;
		toRemove = true;
	}
	else if (takingDamage.getElapsedTime() > sf::seconds(0.1))
	{
		if (properties.isRemovable == false)
		{
			return;
		}

		takingDamage.restart();
		health -= damage;
		if (health <= 0)
		{
			toRemove = true;
		}
	}
}