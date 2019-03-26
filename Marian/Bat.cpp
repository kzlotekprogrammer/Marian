//Bat::Bat(b2World * t_world, sf::Color t_id, sf::Vector2f t_positionSFML, Entity * t_entity) : Enemy(t_world)
//{
//    id = t_id;
//    entity = t_entity;
//    rect_x = 26;
//    rect_y = 8;
//
//    nowRect = 1;
//    maxRect = 2;
//
//    properties.isDangerous = true;
//    properties.isRemovable = true;
//
//    //Box2D body
//    b2BodyDef bodyDef;
//    bodyDef.fixedRotation = true;
//    bodyDef.userData = this;
//    bodyDef.type = b2_dynamicBody;
//    bodyDef.position = b2Vec2(SFtoB2D(t_positionSFML.x), SFtoB2D(-t_positionSFML.y));
//    body = world->CreateBody(&bodyDef);
//    body->SetGravityScale(0);
//
//    //Box2d shape
//    b2PolygonShape polygon;
//    b2Vec2 vertices[8];
//    vertices[0] = b2Vec2(SFtoB2D(0+10+5), SFtoB2D(0-5));
//    vertices[1] = b2Vec2(SFtoB2D(0+10), SFtoB2D(0-5-5));
//    vertices[2] = b2Vec2(SFtoB2D(0+10), SFtoB2D(-64+3));
//    vertices[3] = b2Vec2(SFtoB2D(0+10+10), SFtoB2D(-64));
//    vertices[4] = b2Vec2(SFtoB2D(64-10-10), SFtoB2D(-64));
//    vertices[5] = b2Vec2(SFtoB2D(64-10), SFtoB2D(-64+3));
//    vertices[6] = b2Vec2(SFtoB2D(64-10), SFtoB2D(0-5-5));
//    vertices[7] = b2Vec2(SFtoB2D(64-10-5), SFtoB2D(0-5));
//    polygon.Set(vertices, 8);
//
//    //Box2d fixture
//    b2FixtureDef fixtureDef;
//    fixtureDef.filter.categoryBits = F_ENEMY;
//    fixtureDef.filter.maskBits = F_PLAYER | F_BULLET | F_WALL;
//    fixtureDef.density = 1.0f;
//    fixtureDef.friction = 0.0f;
//    fixtureDef.shape = &polygon;
//    fixture = body->CreateFixture(&fixtureDef);
//
//    sprite.setPosition(t_positionSFML);
//    sprite.setTextureRect(sf::IntRect(sf::Vector2i(rect_x * 64 + 1, rect_y * 64 - 1), sf::Vector2i(64, 63)));
//}

//Bat::~Bat()
//{
//    world->DestroyBody(body);
//}

//
//void Bat::update()
//{
////    b2Vec2 pos_bat = body->GetPosition();
////    b2Vec2 pos_ent = entity->body->GetPosition();
//
//
//}
