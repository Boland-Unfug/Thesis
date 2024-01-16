// #endif // AGENT_H
#ifndef AGENT_H
#define AGENT_H

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

class Agent
{
public:
    Agent();               // Default constructor
    Agent(int agent_id, b2World &world, float agent_x_position,float agent_y_position); // Constructor with world reference
    void drawAgent(sf::RenderWindow &window);
    void moveAgent(float x_force, float y_force);

    // Setters
    void setAgentXPosition(float x_position);
    void setAgentYPosition(float y_position);
    void setAgentRadius(float radius);
    void setDensity(float density);
    void setFriction(float friction);
    void setRestitution(float restitution);

    // Getters
    float getAgentXPosition();
    float getAgentYPosition();
    float getAgentRadius();
    float getDensity();
    float getFriction();
    float getRestitution();

private:
    int agent_id;
    b2World &world; // Reference to b2World
    static const float SCALE;
    float agent_x_position = 100.f; // Start in the top left corner, will make this dynamic based on the window size later
    float agent_y_position = 100.f;
    float agent_radius = 30.f; // For now this will be 30, will make this dynamic based on the scale later
    float density = 1.0f;      // This should stay static
    float friction = 0.0f;     // This should stay static?
    float restitution = 1.0f;  // This should stay static?
    b2BodyDef bodyDef;
    b2Body *body;
    b2CircleShape dynamicCircle;
    b2FixtureDef fixtureDef;
    sf::CircleShape agent_body;
};

#endif // AGENT_H
