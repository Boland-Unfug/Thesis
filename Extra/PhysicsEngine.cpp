#include "PhysicsEngine.h"
#include <iostream>

PhysicsEngine::PhysicsEngine()
{ // default constructor
    world = new b2World(b2Vec2(0.0f, 0.0f));
    // In your setup, you need to register the contact listener
}

PhysicsEngine::PhysicsEngine(b2Vec2 gravity /*,b2ContactListener* listener*/)
{ // constructor with gravity and listener TODO move listener so I don't need it as an input
    world = new b2World(gravity);
}

PhysicsEngine::~PhysicsEngine()
{
    delete world;
}

b2Body *PhysicsEngine::CreateWall(const b2Vec2 &position, const b2Vec2 &size)
{
    // Hand this meters, not pixels (divide by 30)
    b2BodyDef bodyDef;
    bodyDef.position = position;
    b2Body *body = world->CreateBody(&bodyDef);

    b2PolygonShape box;
    box.SetAsBox(size.x / 2, size.y / 2);

    body->CreateFixture(&box, 0.0f);

    return body;
}

b2Body *PhysicsEngine::CreateCircle(int id, const b2Vec2 &position, float radius, float density, float friction, float restitution)
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = position;
    uintptr_t pointer = (uintptr_t)id;
    bodyDef.userData.pointer = pointer;
    b2Body *body = world->CreateBody(&bodyDef);

    b2CircleShape circle;
    circle.m_radius = radius;

    b2FixtureDef fixtureDef; // define the fixture, which defines the physics to apply to the body
    fixtureDef.shape = &circle;
    fixtureDef.density = density;
    fixtureDef.friction = friction;
    fixtureDef.restitution = restitution;

    body->CreateFixture(&fixtureDef);

    return body;
}

void PhysicsEngine::PushCircle(b2Body *body, const b2Vec2 &force)
{
    body->ApplyLinearImpulse(force, body->GetWorldCenter(), true);
}

void PhysicsEngine::Step(float timeStep, int velocityIterations, int positionIterations)
{
    world->Step(timeStep, velocityIterations, positionIterations);
}

b2World &PhysicsEngine::getWorld()
{
    return *world;
}