#include "Bullet.h"

Bullet::Bullet(b2World * t_world, sf::Vector2f t_positionSFML, Entity * t_whoIsShooting, float t_maxSpeed) 
	: Entity(t_world, t_positionSFML, 32, 37)
{
    //data
    id = sf::Color(100, 100, 100);
    whoIsShooting = t_whoIsShooting;
    maxSpeed = t_maxSpeed;
    properties.type = BULLET;
    properties.isDangerous = true;
    properties.isRemovable = true;
    rect_now = 1;
    rect_max = 4;

    //Box2D body
    body->SetBullet(true);
    body->SetGravityScale(0);
    body->SetType(b2_dynamicBody);
    body->SetUserData(this);

    //Box2D shape
    b2CircleShape circle;
    circle.m_radius = 0.1f;
    circle.m_p = b2Vec2(SFtoB2D(32), SFtoB2D(-32));

    //Box2D fixture
    b2FixtureDef fixtureDef;
    fixtureDef.filter.categoryBits = F_BULLET;
    fixtureDef.filter.maskBits = F_PLAYER | F_ENEMY | F_WALL;
    fixtureDef.shape = &circle;
    fixtureDef.friction = 0.0f;
    fixtureDef.density = 1.0f;
    fixture = body->CreateFixture(&fixtureDef);
}

Bullet::~Bullet()
{

}

void Bullet::update()
{
    move();

    if(animationClock.getElapsedTime().asSeconds() > 0.1f)
    {
        rect_now++;
        if(rect_now > rect_max)
            rect_now = rect_max;
        sprite.setTextureRect(sf::IntRect(sf::Vector2i(rect_x * 64,(rect_y+rect_now-1) * 64 + 1), sf::Vector2i(64, 64)));
        animationClock.restart();
    }

    Entity::update();
}

void Bullet::move()
{
    float dt = movingClock.restart().asSeconds();
    b2Vec2 vel = body->GetLinearVelocity();

    if(abs(vel.x) < abs(maxSpeed))
    {
        float force = maxSpeed*dt/(1.0f/60)/10;
        body->ApplyForce(b2Vec2(force, 0), body->GetWorldCenter(), true);
    }
}
