#ifndef PHYSICSENGINE_H
#define PHYSICSENGINE_H

#include <Box2D/Box2D.h>

class PhysicsEngine {
public:
    PhysicsEngine();
    PhysicsEngine(b2Vec2 gravity, b2ContactListener* listener);
    ~PhysicsEngine();

    b2Body* CreateWall(const b2Vec2& position, const b2Vec2& size);
    b2Body* CreateAgent(const b2Vec2& position, float radius);
    void PushAgent(b2Body* body, const b2Vec2& force);

    void Step(float timeStep, int velocityIterations, int positionIterations);

    // WIll also need collision detection
    // Getters
    b2World& getWorld();
    


private:
    b2World* world;
};

#endif // PHYSICSENGINE_H
