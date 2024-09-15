#include <iostream>

#include "RenderingEngine.h"
#include "PhysicsEngine.h"

int main(){
    std::cout << "Hello World" << std::endl;

    // Create a rendering engine
    RenderingEngine renderingEngine;

    std::cout << "Rendering engine created" << std::endl;

    sf::RenderWindow window(sf::VideoMode(900.0f, 900.0f), "SFML window");
    window.setFramerateLimit(60);

    std::cout << "Window created" << std::endl;

    // Create a physics engine
    PhysicsEngine physicsEngine(b2Vec2(0.0f, 0.0f));

    std::cout << "Physics engine created" << std::endl;

    // Create 4 walls
    physicsEngine.CreateWall(b2Vec2(0.f, 0.f), b2Vec2(60.f, 1.f));
    physicsEngine.CreateWall(b2Vec2(0.f, 0.f), b2Vec2(1.f, 60.f));
    physicsEngine.CreateWall(b2Vec2(0.f, 30.f), b2Vec2(60.f, 1.f));
    physicsEngine.CreateWall(b2Vec2(30.f, 0.f), b2Vec2(1.f, 60.f));

    std::cout << "Walls created" << std::endl;

    // Constants
    const int numAgents = 1000; // TODO make this dynamic later
    const float agentRadius = 0.3f;

    std::cout << "Constants created" << std::endl;

    // make the needed vectors
    b2Body *bodies[numAgents]; // array of body pointers
    for (int i = 0; i < numAgents; i++)
    {
        bodies[i] = nullptr;
    }
    sf::Color colors[numAgents]; // array of colors (I want different colors available)
    std::cout << "Vectors created" << std::endl;

    
    int round = 0;
    while (window.isOpen())
    {
        std::cout << "Round " << round << std::endl;
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

        if (round < numAgents)
        {
            bodies[round] = physicsEngine.CreateCircle(round, b2Vec2(1.0f, 1.0f), agentRadius);
            colors[round] = sf::Color::Red;
            physicsEngine.PushCircle(bodies[round], b2Vec2(10.f, 10.f));
        }

        // Update the physics engine
        b2Contact *contacts = physicsEngine.Step(1.f / 60.f, 8, 3);

        // update the rendering engine
        renderingEngine.Update(window, bodies, colors, numAgents);


        round += 1;
    }
    return 0;   
}