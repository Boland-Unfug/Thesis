#include <box2d/box2d.h>
#include <iostream>
#include <vector>
#include "Game.h"

// Collision detection
class MyContactListener : public b2ContactListener
{

public:
    MyContactListener(Game *game) : b2ContactListener() {}

    void BeginContact(b2Contact *contact) override
    {
        b2Body *body1 = contact->GetFixtureA()->GetBody();
        b2Body *body2 = contact->GetFixtureB()->GetBody();
        if (body1->GetUserData().pointer == 0 || body2->GetUserData().pointer == 0)
        {
            return;
        }

        Agent *agent1 = reinterpret_cast<Agent *>(body1->GetUserData().pointer);
        Agent *agent2 = reinterpret_cast<Agent *>(body2->GetUserData().pointer);


        if (agent1 != nullptr && agent2 != nullptr){
            // Play A game
            game->play(*agent1, *agent2);
        }
    }

    void EndContact(b2Contact *contact) override
    {
        // Called when two fixtures begin to touch
        // b2Fixture* fixtureA = contact->GetFixtureA();
        // b2Fixture* fixtureB = contact->GetFixtureB();
        // std::cout << "Agent A fixture" << fixtureA << std::endl;
        // std::cout << "Agent B fixture" << fixtureB << std::endl;
        // // Get the bodies
        // b2Body* bodyA = fixtureA->GetBody();
        // b2Body* bodyB = fixtureB->GetBody();

        // std::cout << "Agent A body" << bodyA << std::endl;
        // std::cout << "Agent B body" << bodyB << std::endl;

        // // Check the pointers, reinterpret_cast
        // Agent* agentA = reinterpret_cast<Agent*>(bodyA->GetUserData().pointer);
        // Agent* agentB = reinterpret_cast<Agent*>(bodyB->GetUserData().pointer);

        // std::cout << "Agent A" << agentA << std::endl;
        // std::cout << "Agent B" << agentB << std::endl;
        // if (agentA != nullptr && agentB != nullptr) {
        //     std::cout << "Agents are not null" << std::endl;
        //     game->play(*agentA, *agentB);
        //     std::cout << "Agent A score" << agentA->getScore() << std::endl;
        //     std::cout << "Agent B score" << agentB->getScore() << std::endl;
        //     // Play A game
        //     game->play(*agentA, *agentB);
        // }
    }

private:
    Game *game;
};