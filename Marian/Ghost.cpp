#include "Ghost.h"

Ghost::Ghost(b2World * t_world, sf::Vector2f t_positionSFML, int t_rect_x, int t_rect_y) : Enemy(t_world, t_positionSFML, t_rect_x, t_rect_y)
{
    //data
    firstFrame = 1;
    nowFrame = firstFrame;
    maxFrame = 2;

    //Box2D body
    body->SetType(b2_dynamicBody);
    body->SetGravityScale(0);

    //Box2d shape
    b2PolygonShape polygon;
    b2Vec2 vertices[8];
    vertices[0] = b2Vec2(SFtoB2D(15), SFtoB2D(-5));
    vertices[1] = b2Vec2(SFtoB2D(10), SFtoB2D(-10));
    vertices[2] = b2Vec2(SFtoB2D(10), SFtoB2D(-51));
    vertices[3] = b2Vec2(SFtoB2D(20), SFtoB2D(-54));
    vertices[4] = b2Vec2(SFtoB2D(44), SFtoB2D(-54));
    vertices[5] = b2Vec2(SFtoB2D(54), SFtoB2D(-51));
    vertices[6] = b2Vec2(SFtoB2D(54), SFtoB2D(-10));
    vertices[7] = b2Vec2(SFtoB2D(49), SFtoB2D(-5));
    polygon.Set(vertices, 8);

    //Box2d fixture
    b2FixtureDef fixtureDef;
    fixtureDef.filter.categoryBits = F_ENEMY;
    fixtureDef.filter.maskBits = F_PLAYER | F_BULLET | F_WALL;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.0f;
    fixtureDef.shape = &polygon;
    fixture = body->CreateFixture(&fixtureDef);

    //Box2d sensor
    b2Vec2 vert_sensor[4];
    vert_sensor[0] = b2Vec2(SFtoB2D(0), SFtoB2D(-15));
    vert_sensor[1] = b2Vec2(SFtoB2D(0), SFtoB2D(-50));
    vert_sensor[2] = b2Vec2(SFtoB2D(10), SFtoB2D(-50));
    vert_sensor[3] = b2Vec2(SFtoB2D(10), SFtoB2D(-15));
    polygon.Set(vert_sensor, 4);
    fixtureDef.isSensor = true;
    sensorFixture[0] = body->CreateFixture(&fixtureDef);

    vert_sensor[0] = b2Vec2(SFtoB2D(54), SFtoB2D(-15));
    vert_sensor[1] = b2Vec2(SFtoB2D(54), SFtoB2D(-50));
    vert_sensor[2] = b2Vec2(SFtoB2D(64), SFtoB2D(-50));
    vert_sensor[3] = b2Vec2(SFtoB2D(64), SFtoB2D(-15));
    polygon.Set(vert_sensor, 4);
    sensorFixture[1] = body->CreateFixture(&fixtureDef);
}

Ghost::~Ghost()
{

}

void Ghost::update()
{
    move();

    if(animationClock.getElapsedTime().asSeconds() > 0.2f)
    {
        nowFrame++;
        if(nowFrame > maxFrame)
            nowFrame = firstFrame;

        animationClock.restart();
    }

    if(directionOfMoving == D_LEFT)
    {
        sprite.setTextureRect(sf::IntRect(sf::Vector2i((rect_x+nowFrame-1) * 64, rect_y * 64), sf::Vector2i(-63, 64)));

        MyQueryCallback myQueryCallback_1(this);
        b2AABB aabb;
        sensorFixture[0]->GetShape()->ComputeAABB(&aabb, sensorFixture[0]->GetBody()->GetTransform(), 0);
        world->QueryAABB(&myQueryCallback_1, aabb);

        if(myQueryCallback_1.howMany)
            changeDirection();
    }
    else
    {
        sprite.setTextureRect(sf::IntRect(sf::Vector2i((rect_x+nowFrame-2) * 64, rect_y * 64), sf::Vector2i(63, 64)));

        MyQueryCallback myQueryCallback_1(this);
        b2AABB aabb;
        sensorFixture[1]->GetShape()->ComputeAABB(&aabb, sensorFixture[1]->GetBody()->GetTransform(), 0);
        world->QueryAABB(&myQueryCallback_1, aabb);

        if(myQueryCallback_1.howMany)
            changeDirection();
    }

    Enemy::update();
}

Ghost::MyQueryCallback::MyQueryCallback(Ghost * t_ghost)
{
    ghost = t_ghost;
    howMany = 0;
}

bool Ghost::MyQueryCallback::ReportFixture(b2Fixture * fixture)
{
    if(fixture == ghost->fixture || fixture == ghost->sensorFixture[0] || fixture == ghost->sensorFixture[1])
        return true;

    if(fixture->IsSensor())
        return true;

    if(fixture->GetFilterData().categoryBits & F_ENEMY)
        return true;

    howMany++;
    return false;
}
