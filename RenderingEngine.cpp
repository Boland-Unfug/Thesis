#include "RenderingEngine.h"

void RenderingEngine::drawAgent(sf::RenderWindow &window, b2Body *body, sf::Color color)
{
    b2Fixture *fixture = body->GetFixtureList();
    b2CircleShape *circleShape = static_cast<b2CircleShape *>(fixture->GetShape());
    float radius = circleShape->m_radius;


    sf::CircleShape circle(radius * SCALE);
    circle.setOrigin(radius * SCALE, radius * SCALE);
    circle.setPosition(SCALE * body->GetPosition().x, SCALE * body->GetPosition().y);
    circle.setRotation(body->GetAngle() * 180.0f / b2_pi);

    circle.setFillColor(color);

    window.draw(circle);
};
