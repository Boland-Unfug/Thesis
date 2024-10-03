#pragma once
#ifndef RENDERINGENGINE_H
#define RENDERINGENGINE_H


#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

class RenderingEngine {
public:
    void DrawCircle(sf::RenderWindow &window, b2Body *body, sf::Color color); // Draw an agent
    void Update(sf::RenderWindow &window, b2Body* bodies[], int size); // Update the window with the new positions of the agents
    // TODO might add more drawing functions

private:
    const float SCALE = 30.f; // 30 pixels per meter, only universal constant
};

#endif // RENDERINGENGINE_H