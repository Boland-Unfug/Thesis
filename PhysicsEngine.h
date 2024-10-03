#pragma once
#ifndef PHYSICSENGINE_H
#define PHYSICSENGINE_H

#include <Box2D/Box2D.h>

class PhysicsEngine {

public:
    PhysicsEngine();
    PhysicsEngine(b2Vec2 gravity/*, b2ContactListener* listener*/);
    ~PhysicsEngine();

    b2Body* CreateWall(const b2Vec2& position, const b2Vec2& size);
    b2Body* CreateCircle(int id, const b2Vec2& position, float radius, float density = 1.0f, float friction = 0.1f, float restitution = 1.0f);
    void PushCircle(b2Body* body, const b2Vec2& force);

    b2Contact* Step(float timeStep, int velocityIterations, int positionIterations);

    // TODO collision listener
    // Getters
    b2World& getWorld();


private:
    b2World* world;
};

#endif // PHYSICSENGINE_H
