#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include "PhysicsEngine.cpp"
#include "RenderingEngine.cpp"
#include "Agent.cpp"
#include "Game.cpp"
#include "CollisionListener.cpp"

#include <iostream>
#include <vector>




int main() {

    // Create the main window
    sf::RenderWindow window(sf::VideoMode(900.0f, 900.0f), "SFML window");
    
    b2ContactListener* collisionListener = new MyContactListener();
    PhysicsEngine physicsEngine(b2Vec2(0.0f, 0.0f), collisionListener);

    b2World& world = physicsEngine.getWorld();

    //Create 100 agents
    std::vector<Agent> agents;
    for (int i = 0; i < 2; i++) {
        agents.push_back(Agent(physicsEngine.CreateAgent(b2Vec2(2.f*i, 10.f), 2.f), i));
        agents[i].connectAgentToBody();
    }

    // Get a list of agent pointers
    std::vector<Agent*> agentPointers;
    for (Agent agent : agents) {
        agentPointers.push_back(&agent);
    }

    
    // Push the agent
    physicsEngine.PushAgent(agents[0].getBody(), b2Vec2(10.f, 10.f));



    // Create 4 walls
    physicsEngine.CreateWall(b2Vec2(0.f, 0.f), b2Vec2(60.f, 1.f));
    physicsEngine.CreateWall(b2Vec2(0.f, 0.f), b2Vec2(1.f, 60.f));
    physicsEngine.CreateWall(b2Vec2(0.f, 30.f), b2Vec2(60.f, 1.f));
    physicsEngine.CreateWall(b2Vec2(30.f, 0.f), b2Vec2(1.f, 60.f));

    // Create a rendering engine
    RenderingEngine renderingEngine;

    // Render loop
    while (window.isOpen()) {
        // Process events
        sf::Event event;
        while (window.pollEvent(event)) {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Update the physics engine
        physicsEngine.Step(1.f / 60.f, 8, 3);



        // Clear screen
        window.clear();

        // Draw the circles
        for (Agent agent : agents){
            renderingEngine.drawAgent(window, agent.getBody(), sf::Color::Red);
        }

        // Update the window
        window.display();
    }

    return 0;
}