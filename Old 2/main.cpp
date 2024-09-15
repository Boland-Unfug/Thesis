#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include "PhysicsEngine.cpp"
#include "RenderingEngine.cpp"
#include "Agent.cpp"
#include "Game.cpp"
#include "CollisionListener.cpp"
#include "GameTactics.h"
#include "GameManeuvers.h"

#include <iostream>
#include <vector>


int main() {
    // I need to write static_cast<int> to print the value of the signed char to print it as an integer

    // Create the main window
    sf::RenderWindow window(sf::VideoMode(900.0f, 900.0f), "SFML window");
    window.setFramerateLimit(100);

    Game game;
    // Get the pointer
    Game* gamePointer = &game;
    
    b2ContactListener* collisionListener = new MyContactListener(gamePointer);
    PhysicsEngine physicsEngine(b2Vec2(0.0f, 0.0f), collisionListener);

    //Create 100 agents
    std::vector<Agent> agents;
    // This seems to cause a lot of problems, possibly because the copy function when pushing & pointers
    for (int i = 1; i < 100; i++) {
        Agent *agent = new Agent(physicsEngine.CreateAgent(b2Vec2(1.0f, 1.0f), 0.2f), i);
        agent->connectAgentToBody();
        if (i % 2 == 0) {
            agent->setTactic(new Defect());
        } else {
            agent->setTactic(new Cooperate());
        }
        if (i % 4 == 0) {
            agent->setManeuver(new Up());
        } else if (i % 3 == 0) {
            agent->setManeuver(new Down());
        } else if (i % 2 == 0) {
            agent->setManeuver(new Left());
        } else {
            agent->setManeuver(new Right());
        }


        agents.push_back(*agent);
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

        // Move the agents
        for (Agent agent : agents) {
            // get the game maneuver of the agent
            physicsEngine.PushAgent(agent.getBody(), agent.doManeuver());
        }

        // Draw the circles
        for (Agent agent : agents){
            renderingEngine.drawAgent(window, agent.getBody(), sf::Color::Red);
        }

        // Update the window
        window.display();
    }

    return 0;
}