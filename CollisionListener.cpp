#include <box2d/box2d.h>
#include <iostream>

// Collision detection
class MyContactListener : public b2ContactListener {
    void BeginContact(b2Contact* contact) override {
        // Called when two fixtures begin to touch
        b2Fixture* fixtureA = contact->GetFixtureA();
        b2Fixture* fixtureB = contact->GetFixtureB();
        std::cout << fixtureA->GetUserData().pointer << std::endl;
        std::cout << fixtureB->GetUserData().pointer << std::endl;
        int agentA_id = fixtureA->GetUserData().pointer;
        int agentB_id = fixtureB->GetUserData().pointer;
        std::cout << "Begin contact between " << agentA_id << " and " << agentB_id << std::endl;
        // ... Handle the beginning of a contact
    }

    void EndContact(b2Contact* contact) override {
        // Called when two fixtures cease to touch
        std::cout << "End contact" << std::endl;
        // ... Handle the end of a contact
    }
};