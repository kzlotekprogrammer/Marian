#include "Skeleton.h"

Skeleton::Skeleton(b2World * t_world, sf::Vector2f t_positionSFML, int t_rect_x, int t_rect_y) : Enemy(t_world, t_positionSFML, t_rect_x, t_rect_y)
{
     //data
    firstFrame = 1;
    nowFrame = firstFrame;
    maxFrame = 2;

    //Box2D body
    body->SetUserData(this);

    //Box2d shape
    b2PolygonShape polygon;
    b2Vec2 vertices[8];
    vertices[0] = b2Vec2(SFtoB2D(15), SFtoB2D(-5));
    vertices[1] = b2Vec2(SFtoB2D(10), SFtoB2D(-10));
    vertices[2] = b2Vec2(SFtoB2D(10), SFtoB2D(-61));
    vertices[3] = b2Vec2(SFtoB2D(20), SFtoB2D(-64));
    vertices[4] = b2Vec2(SFtoB2D(44), SFtoB2D(-64));
    vertices[5] = b2Vec2(SFtoB2D(54), SFtoB2D(-61));
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

    //Sensor 1
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

    //Sensor 2
    vert_sensor[0] = b2Vec2(SFtoB2D(-50), SFtoB2D(-74));
    vert_sensor[1] = b2Vec2(SFtoB2D(-50), SFtoB2D(-84));
    vert_sensor[2] = b2Vec2(SFtoB2D(-20), SFtoB2D(-84));
    vert_sensor[3] = b2Vec2(SFtoB2D(-20), SFtoB2D(-74));
    polygon.Set(vert_sensor, 4);
    sensorFixture[2] = body->CreateFixture(&fixtureDef);

    vert_sensor[0] = b2Vec2(SFtoB2D(84), SFtoB2D(-74));
    vert_sensor[1] = b2Vec2(SFtoB2D(84), SFtoB2D(-84));
    vert_sensor[2] = b2Vec2(SFtoB2D(114), SFtoB2D(-84));
    vert_sensor[3] = b2Vec2(SFtoB2D(114), SFtoB2D(-74));
    polygon.Set(vert_sensor, 4);
    sensorFixture[3] = body->CreateFixture(&fixtureDef);
}

Skeleton::~Skeleton()
{

}

void Skeleton::update()
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
        sprite.setTextureRect(sf::IntRect(sf::Vector2i((rect_x+nowFrame-1) * 64 + 1, rect_y * 64), sf::Vector2i(-64, 63)));

        MyQueryCallback myQueryCallback_1(this);
        b2AABB aabb;
        sensorFixture[0]->GetShape()->ComputeAABB(&aabb, sensorFixture[0]->GetBody()->GetTransform(), 0);
        world->QueryAABB(&myQueryCallback_1, aabb);

        if(myQueryCallback_1.howMany)
        {
            changeDirection();
        }
        else
        {
            MyQueryCallback myQueryCallback_2(this);
            b2AABB aabb_2;
            sensorFixture[2]->GetShape()->ComputeAABB(&aabb_2, sensorFixture[2]->GetBody()->GetTransform(), 0);
            world->QueryAABB(&myQueryCallback_2, aabb_2);

            if(!myQueryCallback_2.howMany)
            {
                changeDirection();
            }
        }
    }
    else
    {
        sprite.setTextureRect(sf::IntRect(sf::Vector2i((rect_x+nowFrame-2) * 64 + 1, rect_y * 64), sf::Vector2i(64, 63)));

        MyQueryCallback myQueryCallback_1(this);
        b2AABB aabb;
        sensorFixture[1]->GetShape()->ComputeAABB(&aabb, sensorFixture[1]->GetBody()->GetTransform(), 0);
        world->QueryAABB(&myQueryCallback_1, aabb);

        if(myQueryCallback_1.howMany)
        {
            changeDirection();
        }
        else
        {
            MyQueryCallback myQueryCallback_2(this);
            b2AABB aabb_2;
            sensorFixture[3]->GetShape()->ComputeAABB(&aabb_2, sensorFixture[3]->GetBody()->GetTransform(), 0);
            world->QueryAABB(&myQueryCallback_2, aabb_2);

            if(!myQueryCallback_2.howMany)
            {
                changeDirection();
            }
        }
    }

    Enemy::update();
}

Skeleton::MyQueryCallback::MyQueryCallback(Skeleton * t_skeleton)
{
    skeleton = t_skeleton;
    howMany = 0;
}

bool Skeleton::MyQueryCallback::ReportFixture(b2Fixture * fixture)
{
    if(fixture == skeleton->fixture)
        return true;

    for(int i = 0; i < 4; i++)
    {
        if(fixture == skeleton->sensorFixture[i])
            return true;
    }

    if(fixture->IsSensor())
        return true;

    if(fixture->GetFilterData().categoryBits & F_ENEMY)
        return true;

    howMany++;
    return false;
}
