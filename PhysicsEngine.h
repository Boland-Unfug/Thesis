#ifndef PHYSICSENGINE_H
#define PHYSICSENGINE_H

#include <Box2D/Box2D.h>

class PhysicsEngine {
public:
    PhysicsEngine();
    PhysicsEngine(b2Vec2 gravity);
    ~PhysicsEngine();

    b2Body* CreateWall(const b2Vec2& position, const b2Vec2& size);
    b2Body* CreateAgent(const b2Vec2& position, float radius);
    void PushAgent(b2Body* body, const b2Vec2& force);

    // Getters
    b2World& getWorld();


private:
    b2World* world;
};

#endif // PHYSICSENGINE_H
