#include <iostream>

#include "RenderingEngine.h"

void RenderingEngine::DrawCircle(sf::RenderWindow &window, b2Body *body, sf::Color color) // TODO simplify this function, I can likely get away with storing a position and just handing it that
{
    b2Fixture *fixture = body->GetFixtureList();
    b2CircleShape *circleShape = static_cast<b2CircleShape *>(fixture->GetShape());
    float radius = circleShape->m_radius;

    // I thought about doing this process in an array and handing it in, but tbh its just extra work
    // Nothing I can do to avoid body pointers and extraction of the position
    sf::CircleShape circle(radius * SCALE);
    circle.setOrigin(radius * SCALE, radius * SCALE);
    circle.setPosition(SCALE * body->GetPosition().x, SCALE * body->GetPosition().y);
    circle.setRotation(body->GetAngle() * 180.0f / b2_pi);

    circle.setFillColor(color);

    window.draw(circle);
};

void RenderingEngine::Update(sf::RenderWindow &window, b2Body* bodies[], sf::Color colors[], int size)
{

    // clear the window
    window.clear();

    std::cout<<" Flag 1"<<std::endl;
    // Draw the circles
    for (int i = 0; i < (size - 1); i++)
    {
        std::cout<<" Flag 2"<<std::endl;
        if (bodies[i] != nullptr){
            std::cout<<" Flag 3"<<std::endl;
            RenderingEngine::DrawCircle(window, bodies[i], colors[i]);};
    }
    std::cout<<" Flag 4"<<std::endl;
    // Update the window
    window.display(); // here is the error???
    std::cout<<" Flag 5"<<std::endl;
}