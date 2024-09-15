#include <iostream>
#include <vector>
#include <bitset>

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include "PhysicsEngine.h"
#include "RenderingEngine.h"

int main()
{

    // The rendering should not be a problem, loaded 100000 in ~1 second

    // TODO: make all functions more flexible, have to prep for eventual in app customization features

    // improve the agent creation so there is less overlapping agents (use a feed system) DONE
    // Next I need to make it so that agents that go in early don't have an advantage, but later

    // make the simple agent? what does it even store? nothing the 'agent' here is the array positioni

    // before I can move the game class, I have to set up collision detection DONE

    // Move over game class
    // connect game class to collision
    // possibly set up listener in main loop? or in physics engine, I could return a list of collisions to main.

    // Move over history class
    // Make history save to a file

    // set up maneuvers
    // I can just have it return a b2vec2 of forces to apply store it in its own array
    // I will set that array to 0 between, so it only pushes agents once and maybe every 10 rounds or something

    // set up tactics
    // unsure for now

    std::cout << "Starting program" << std::endl;

    // Create a rendering engine
    RenderingEngine renderingEngine;

    // Create the main window
    sf::RenderWindow window(sf::VideoMode(900.0f, 900.0f), "SFML window");
    window.setFramerateLimit(60);

    // Create a physics engine
    PhysicsEngine physicsEngine(b2Vec2(0.0f, 0.0f));

    // Create 4 walls
    physicsEngine.CreateWall(b2Vec2(0.f, 0.f), b2Vec2(60.f, 1.f));
    physicsEngine.CreateWall(b2Vec2(0.f, 0.f), b2Vec2(1.f, 60.f));
    physicsEngine.CreateWall(b2Vec2(0.f, 30.f), b2Vec2(60.f, 1.f));
    physicsEngine.CreateWall(b2Vec2(30.f, 0.f), b2Vec2(1.f, 60.f));

    // Constants
    const int numAgents = 100; // TODO make this dynamic later
    const float agentRadius = 0.3f;

    // make the needed vectors
    b2Body *bodies[numAgents]; // array of body pointers
    for (int i = 0; i < numAgents; i++)
    {
        bodies[i] = nullptr;
    }
    sf::Color colors[numAgents];                // array of colors (I want different colors available


    // game loop
    int round = 0;
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        // add one agent each round, until the number of agents is reached
        if (round < numAgents)
        {
            bodies[round] = physicsEngine.CreateCircle(round, b2Vec2(1.0f, 1.0f), agentRadius);
            colors[round] = sf::Color::Red;
            physicsEngine.PushCircle(bodies[round], b2Vec2(10.f, 10.f));
        }

        std::bitset<numAgents> collisions[numAgents] = {0}; // 0 means no collision, 1 means collision

        // Update the physics
        b2Contact *contacts = physicsEngine.Step(1.f / 60.f, 8, 3);

        for (b2Contact* contact = contacts; contact; contact = contact->GetNext())
        {

            int id1 = contact->GetFixtureA()->GetBody()->GetUserData().pointer;
            int id2 = contact->GetFixtureB()->GetBody()->GetUserData().pointer;

            // flip the ids if they are out of order
            if (id1 > id2){
                int temp = id1;
                id1 = id2;
                id2 = temp;
            }

            if (collisions[id1][id2] == 0) {
                collisions[id1][id2] = 1;
                // here is where I will play the game
            }
        }

        // update the rendering engine
        renderingEngine.Update(window, bodies, colors, numAgents);
        round += 1;
    }
    return 0;
}