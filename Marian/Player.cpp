#include "Player.h"

Player::Player(b2World * t_world, sf::Vector2f t_positionSFML) : Entity(t_world, t_positionSFML, 26, 1)
{
    //data
    id = ID_PLAYER;
    moveState = MS_STOP;
    directionTexture = MS_RIGHT;

    nowFrame = 1;
    properties.type = PLAYER;

    //Box2D body
    body->SetUserData(this);
    body->SetType(b2_dynamicBody);

    //Box2D shape
    b2PolygonShape polygon;
    b2Vec2 vertices[8];
    vertices[0] = b2Vec2(SFtoB2D(15), SFtoB2D(-10));
    vertices[1] = b2Vec2(SFtoB2D(10), SFtoB2D(-15));
    vertices[2] = b2Vec2(SFtoB2D(10), SFtoB2D(-61));
    vertices[3] = b2Vec2(SFtoB2D(20), SFtoB2D(-64));
    vertices[4] = b2Vec2(SFtoB2D(44), SFtoB2D(-64));
    vertices[5] = b2Vec2(SFtoB2D(54), SFtoB2D(-61));
    vertices[6] = b2Vec2(SFtoB2D(54), SFtoB2D(-15));
    vertices[7] = b2Vec2(SFtoB2D(49), SFtoB2D(-10));
    polygon.Set(vertices, 8);

    //Box2D fixture
    b2FixtureDef fixtureDef;
    fixtureDef.filter.categoryBits = F_PLAYER;
    fixtureDef.filter.maskBits = F_BULLET | F_ENEMY | F_WALL;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.0f;
    fixtureDef.shape = &polygon;
    fixture = body->CreateFixture(&fixtureDef);

    //Box2D lowerSensorFixture
    b2Vec2 vertices_lower[4];
    vertices_lower[0] = b2Vec2(SFtoB2D(20), SFtoB2D(-73));
    vertices_lower[1] = b2Vec2(SFtoB2D(20), SFtoB2D(-88));
    vertices_lower[2] = b2Vec2(SFtoB2D(44), SFtoB2D(-88));
    vertices_lower[3] = b2Vec2(SFtoB2D(44), SFtoB2D(-73));
    polygon.Set(vertices_lower, 4);
    fixtureDef.isSensor = true;
    lowerSensorFixture = body->CreateFixture(&fixtureDef);

    //Box2D upperSensorFixture
    vertices_lower[0] = b2Vec2(SFtoB2D(30), SFtoB2D(-10));
    vertices_lower[1] = b2Vec2(SFtoB2D(30), SFtoB2D(-20));
    vertices_lower[2] = b2Vec2(SFtoB2D(44), SFtoB2D(-20));
    vertices_lower[3] = b2Vec2(SFtoB2D(44), SFtoB2D(-10));
    polygon.Set(vertices_lower, 4);
    fixtureDef.isSensor = true;
    upperSensorFixture = body->CreateFixture(&fixtureDef);

    //inJump
    inJump = !onGround();

	//items
	coins = 0;
	shooting = false;
	health = 3;
}

Player::~Player()
{

}

void Player::update()
{
    if(inJump)
    {
        jumpClock.restart();

        if(abs(body->GetLinearVelocity().y) < 0.5f && onGround())
        {
            inJump = false;
        }
        else
        {
            if(directionTexture == MS_RIGHT)
            {
                nowFrame = 2;
                sprite.setTextureRect(sf::IntRect(sf::Vector2i((rect_x+nowFrame-1) * 64, rect_y * 64), sf::Vector2i(64, 63)));
            }
            else
            {
                nowFrame = 3;
                sprite.setTextureRect(sf::IntRect(sf::Vector2i((rect_x+nowFrame-1) * 64, rect_y * 64), sf::Vector2i(-64, 63)));
            }
            animationClock.restart();
        }
    }
    else if(moveState == MS_LEFT)
    {
        if(animationClock.getElapsedTime().asSeconds() > 0.2f)
        {
            nowFrame++;
            if(nowFrame > 4)
                nowFrame = 3;
            sprite.setTextureRect(sf::IntRect(sf::Vector2i((rect_x+nowFrame-1) * 64, rect_y * 64), sf::Vector2i(-64, 63)));
            animationClock.restart();
        }
    }
    else if(moveState == MS_RIGHT)
    {
        if(animationClock.getElapsedTime().asSeconds() > 0.2f)
        {
            nowFrame++;
            if(nowFrame > 3)
                nowFrame = 2;
            sprite.setTextureRect(sf::IntRect(sf::Vector2i((rect_x+nowFrame-1) * 64, rect_y * 64), sf::Vector2i(64, 63)));
            animationClock.restart();
        }
    }
    else if(moveState == MS_STOP)
    {
        if(directionTexture == MS_RIGHT)
        {
            nowFrame = 1;
            sprite.setTextureRect(sf::IntRect(sf::Vector2i((rect_x+nowFrame-1) * 64, rect_y * 64), sf::Vector2i(64, 63)));
        }
        else
        {
            nowFrame = 2;
            sprite.setTextureRect(sf::IntRect(sf::Vector2i((rect_x+nowFrame-1) * 64, rect_y * 64), sf::Vector2i(-64, 63)));
        }

        animationClock.restart();
    }

    Entity::update();
}

void Player::stop()
{
    moveState = MS_STOP;
    body->ApplyForce(b2Vec2(body->GetLinearVelocity().x * -10, 0), body->GetWorldCenter(), true);
}

void Player::jump()
{
    if(!inJump && jumpClock.getElapsedTime().asSeconds() >= 0.1f)
    {
        inJump = true;
        float impulse = body->GetMass() * 13;
        body->ApplyLinearImpulse(b2Vec2(0, impulse), body->GetWorldCenter(), true);
    }
}

void Player::bounce()
{
    inJump = true;
    body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x, 0));
    float impulse = body->GetMass() * 8;
    body->ApplyLinearImpulse(b2Vec2(0, impulse), body->GetWorldCenter(), true);
}

void Player::left()
{
    moveState = MS_LEFT;
    if(body->GetLinearVelocity().x > -5)
    {
        float force = -50;
        body->ApplyForce(b2Vec2(force, 0), body->GetWorldCenter(), true);
    }
    if(inJump == false)
    {
        if(directionTexture != MS_LEFT)
        {
            nowFrame = 4;
            animationClock.restart();
        }
    }
    directionTexture = MS_LEFT;
}

void Player::right()
{
    moveState = MS_RIGHT;
    if(body->GetLinearVelocity().x < 5)
    {
        float force = 50;
        body->ApplyForce(b2Vec2(force, 0), body->GetWorldCenter(), true);
    }

    if(inJump == false)
    {
        if(directionTexture != MS_RIGHT)
        {
            nowFrame = 3;
            animationClock.restart();
        }
    }
    directionTexture = MS_RIGHT;
}

bool Player::onGround()
{
    MyQueryCallback myQueryCallback(this);

    b2AABB aabb;
    lowerSensorFixture->GetShape()->ComputeAABB(&aabb, lowerSensorFixture->GetBody()->GetTransform(), 0);

    world->QueryAABB(&myQueryCallback, aabb);

    if(myQueryCallback.howMany)
        return true;
    else
        return false;
}

Bullet * Player::shoot()
{
    if(shootingClock.getElapsedTime().asSeconds() > 0.2f)
    {
        sf::Vector2f positionSFML;
        float maxSpeed;

        if(directionTexture == MS_LEFT)
        {
            positionSFML = sf::Vector2f(B2DtoSF(body->GetPosition().x)-32, B2DtoSF(-body->GetPosition().y));
            maxSpeed = -10;
        }
        else
        {
            positionSFML = sf::Vector2f(B2DtoSF(body->GetPosition().x)+32, B2DtoSF(-body->GetPosition().y));
            maxSpeed = 10;
        }

        Bullet * bullet = new Bullet(world, positionSFML, this, maxSpeed);

        shootingClock.restart();

        return bullet;
    }
    else
    {
        return nullptr;
    }
}

void Player::takeDamage(int damage)
{
	if (damage == 1000)
	{
		health = 0;
		toRemove = true;
	}
	else if (takingDamage.getElapsedTime() > sf::seconds(0.5))
	{
		takingDamage.restart();
		health -= damage;
		if (health <= 0)
		{
			toRemove = true;
		}
	}
}

Player::MyQueryCallback::MyQueryCallback(Player * t_player)
{
    player = t_player;
    howMany = 0;
}

bool Player::MyQueryCallback::ReportFixture(b2Fixture * fixture)
{
    if(fixture == player->lowerSensorFixture || fixture == player->fixture)
        return true;

    if(fixture->IsSensor())
        return true;

    howMany++;
    return false;
}
