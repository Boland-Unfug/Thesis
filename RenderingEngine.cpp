#include "RenderingEngine.h"

void RenderingEngine::drawAgent(sf::RenderWindow &window, b2Body *body)
{ // Only hand this circles
    b2Fixture *fixture = body->GetFixtureList();
    b2CircleShape *circleShape = static_cast<b2CircleShape *>(fixture->GetShape());
    float radius = circleShape->m_radius;

    sf::CircleShape circle(radius * SCALE);
    circle.setOrigin(radius * SCALE, radius * SCALE);
    circle.setPosition(SCALE * body->GetPosition().x, SCALE * body->GetPosition().y);
    circle.setRotation(body->GetAngle() * 180.0f / b2_pi);

    // Set color or texture if needed
    // circle.setFillColor(sf::Color::Red);

    window.draw(circle);
}

void RenderingEngine::drawWall(sf::RenderWindow &window, b2Body *body)
{
    b2Fixture *fixture = body->GetFixtureList();

    b2PolygonShape *polygonShape = static_cast<b2PolygonShape *>(fixture->GetShape());

    // Assuming the polygon is a box (rectangle)
    b2Vec2 *vertices = polygonShape->m_vertices;
    float width = (vertices[1].x - vertices[0].x) * 2.0f;
    float height = (vertices[2].y - vertices[1].y) * 2.0f;

    sf::RectangleShape rectangle(sf::Vector2f(width * SCALE, height * SCALE));
    rectangle.setOrigin(width * SCALE / 2.0f, height * SCALE / 2.0f);
    rectangle.setPosition(SCALE * body->GetPosition().x, SCALE * body->GetPosition().y);
    rectangle.setRotation(body->GetAngle() * 180.0f / b2_pi);

    // Set color or texture if needed
    // rectangle.setFillColor(sf::Color::Green);

    window.draw(rectangle);
}
