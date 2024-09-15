#include "PhysicsEngine.h"



PhysicsEngine::PhysicsEngine() { // default constructor
    world = new b2World(b2Vec2(0.0f, 0.0f));
    // No modifications to the world
}

PhysicsEngine::PhysicsEngine(b2Vec2 gravity, b2ContactListener* listener) {
    world = new b2World(gravity);
    world->SetContactListener(listener);
}

PhysicsEngine::~PhysicsEngine() {
    delete world;
}

b2Body* PhysicsEngine::CreateWall(const b2Vec2& position, const b2Vec2& size) {
    // Hand this meters, not pixels (divide by 30)
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
    fixtureDef.friction = 0.1f;
    fixtureDef.restitution = 1.0f;

    body->CreateFixture(&fixtureDef);

    return body;
}

void PhysicsEngine::PushAgent(b2Body* body, const b2Vec2& force) {
    body->ApplyLinearImpulse(force, body->GetWorldCenter(), true);
}

void PhysicsEngine::Step(float timeStep, int velocityIterations, int positionIterations) {
    world->Step(timeStep, velocityIterations, positionIterations);
}

b2World& PhysicsEngine::getWorld() {
    return *world;
}