#include "PhysicsEngine.h"

PhysicsEngine::PhysicsEngine() { // default constructor
    world = new b2World(b2Vec2(0.0f, 0.0f));
}

PhysicsEngine::PhysicsEngine(b2Vec2 gravity) {
    world = new b2World(gravity);
}

PhysicsEngine::~PhysicsEngine() {
    delete world;
}

b2Body* PhysicsEngine::CreateWall(const b2Vec2& position, const b2Vec2& size) {
    b2BodyDef bodyDef;
    bodyDef.position = position;
    b2Body* body = world->CreateBody(&bodyDef);

    b2PolygonShape box;
    box.SetAsBox(size.x / 2, size.y / 2);

    body->CreateFixture(&box, 0.0f);

    return body;
}

b2Body* PhysicsEngine::CreateAgent(const b2Vec2& position, float radius) {
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = position;
    b2Body* body = world->CreateBody(&bodyDef);

    b2CircleShape circle;
    circle.m_radius = radius;

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &circle;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;

    body->CreateFixture(&fixtureDef);

    return body;
}

void PhysicsEngine::PushAgent(b2Body* body, const b2Vec2& force) {
    body->ApplyForceToCenter(force, true);
}

b2World& PhysicsEngine::getWorld() {
    return *world;
}




