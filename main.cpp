#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include "PhysicsEngine.h"
#include "RenderingEngine.h"

int main(){

    // The rendering should not be a problem, loaded 100000 in ~1 second

    //TODO: make all functions more flexible, have to prep for eventual in app customization features

    // Move over game class
    // connect game class to collision
        //possibly set up listener in main loop? or in physics engine, I could return a list of collisions to main.

    // Move over history class
        // Make history save to a file
    
    // set up maneuvers
        //I can just have it return a b2vec2 of forces to apply store it in its own array
            // I will set that array to 0 between, so it only pushes agents once and maybe every 10 rounds or something

    // set up tactics
        // unsure for now



    // Create a rendering engine
    RenderingEngine renderingEngine;

    // Create the main window
    sf::RenderWindow window(sf::VideoMode(900.0f, 900.0f), "SFML window");
    window.setFramerateLimit(60);

    // Create a physics engine
    PhysicsEngine physicsEngine(b2Vec2(0.0f, 0.0f));

    // Constants
    const int numAgents = 100000; // TODO make this dynamic later
    const float agentRadius = 0.3f;

    // make the needed vectors
    b2Body* bodies[numAgents]; // array of body pointers
    sf::Color colors[numAgents]; // array of colors (I want different colors available)


    for (int i = 0; i < numAgents; i++){
        bodies[i] = physicsEngine.CreateCircle(b2Vec2(1, 1), agentRadius);
        colors[i] = sf::Color::Red;
    }

    // Create 4 walls
    physicsEngine.CreateWall(b2Vec2(0.f, 0.f), b2Vec2(60.f, 1.f));
    physicsEngine.CreateWall(b2Vec2(0.f, 0.f), b2Vec2(1.f, 60.f));
    physicsEngine.CreateWall(b2Vec2(0.f, 30.f), b2Vec2(60.f, 1.f));
    physicsEngine.CreateWall(b2Vec2(30.f, 0.f), b2Vec2(1.f, 60.f));

    // game loop
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
        // physicsEngine.Step(1.f / 60.f, 8, 3);

        // update the rendering engine
        renderingEngine.Update(window, bodies, colors, numAgents);

    }

    return 0;
}