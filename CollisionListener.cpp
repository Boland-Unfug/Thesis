#include <box2d/box2d.h>
#include <iostream>
#include <vector>


// Collision detection
class MyContactListener : public b2ContactListener {

public:
    void BeginContact(b2Contact* contact) override {
        // Called when two fixtures begin to touch
        // b2Fixture* fixtureA = contact->GetFixtureA();
        // b2Fixture* fixtureB = contact->GetFixtureB();
        // // Get the bodies
        // b2Body* bodyA = fixtureA->GetBody();
        // b2Body* bodyB = fixtureB->GetBody();

        // // Check the pointers, reinterpret_cast
        // Agent* agentA = reinterpret_cast<Agent*>(bodyA->GetUserData().pointer);
        // Agent* agentB = reinterpret_cast<Agent*>(bodyB->GetUserData().pointer);

        // std::cout<<agentA<<std::endl;
        // std::cout<<agentB<<std::endl;
        // Get the agents
    

        // ... Handle the beginning of a contact
    }

    void EndContact(b2Contact* contact) override {
        // Called when two fixtures cease to touch
        // std::cout << "End contact" << std::endl;
        // ... Handle the end of a contact
    }
};