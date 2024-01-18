#ifndef RENDERINGENGINE_H
#define RENDERINGENGINE_H


#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

class RenderingEngine {
public:
    void drawAgent(sf::RenderWindow &window, b2Body *body); // Draw an agent
    void drawWall(sf::RenderWindow &window, b2Body *body); // Draw a wall
    // Other rendering-related methods

private:
    const float SCALE = 30.f;
};

#endif // RENDERINGENGINE_H