#include "Agent.h"

const float Agent::SCALE = 30.f;  // Initialize static constant

Agent::Agent(int agent_id, b2World &world, float agent_x_position, float agent_y_position) : world(world), agent_x_position(agent_x_position), agent_y_position(agent_y_position) {
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(agent_x_position / SCALE, agent_y_position / SCALE);
    body = world.CreateBody(&bodyDef);
    dynamicCircle.m_radius = agent_radius / SCALE;
    fixtureDef.shape = &dynamicCircle;
    fixtureDef.density = density;
    fixtureDef.friction = friction;
    fixtureDef.restitution = restitution;
    fixtureDef.userData.pointer = agent_id;
    body->CreateFixture(&fixtureDef);
    agent_body.setRadius(agent_radius);
    agent_body.setFillColor(sf::Color::Red);
    agent_body.setOrigin(agent_radius, agent_radius);
}

void Agent::drawAgent(sf::RenderWindow &window)
{
    b2Vec2 position = body->GetPosition();
    float angle = body->GetAngle();
    agent_body.setPosition(position.x * SCALE, position.y * SCALE);
    agent_body.setRotation(angle * 180.0f / b2_pi);
    window.draw(agent_body);
}

void Agent::moveAgent(float x_force, float y_force)
{
    b2Vec2 force(x_force, y_force);
    body->ApplyForce(force, body->GetWorldCenter(), true);
}

// Setters
void Agent::setAgentXPosition(float x_position)
{
    agent_x_position = x_position;
    agent_body.setPosition(agent_x_position, agent_y_position);
}

void Agent::setAgentYPosition(float y_position)
{
    agent_y_position = y_position;
    agent_body.setPosition(agent_x_position, agent_y_position);
}

void Agent::setAgentRadius(float radius)
{
    agent_radius = radius;
}

void Agent::setDensity(float density)
{
    this->density = density;
}

void Agent::setFriction(float friction)
{
    this->friction = friction;
}

void Agent::setRestitution(float restitution)
{
    this->restitution = restitution;
}

void Agent::setScore(int score)
{
    agent_score = score;
}

// Getters

float Agent::getAgentXPosition()
{
    return agent_x_position;
}

float Agent::getAgentYPosition()
{
    return agent_y_position;
}

float Agent::getAgentRadius()
{
    return agent_radius;
}

float Agent::getDensity()
{
    return density;
}

float Agent::getFriction()
{
    return friction;
}

float Agent::getRestitution()
{
    return restitution;
}

int Agent::getID()
{
    return agent_id;
}

int Agent::getScore()
{
    return agent_score;
}

// ... other methods ...