#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include "PhysicsEngine.cpp"
#include "RenderingEngine.cpp"

#include <iostream>
#include <vector>




int main() {

    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 800), "SFML window");
    
    PhysicsEngine physicsEngine;

    // Create an agent 
    physicsEngine.CreateAgent(b2Vec2(400.f, 400.f), 20.f);

    // Create a wall
    physicsEngine.CreateWall(b2Vec2(400.f, 400.f), b2Vec2(20.f, 20.f));

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

        // Clear screen
        window.clear();

        // Draw the circle
        renderingEngine.drawAgent(window, physicsEngine.getAgentBody());

        // Update the window
        window.display();
    }

    return 0;
}