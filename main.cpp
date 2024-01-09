#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include <box2d/box2d.h>
#include <iostream>

int main() {
    std::cout << "Hello, World!" << std::endl;
    // Create a window with the same pixel depth as the desktop
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Test Window");

    // Main loop that continues until we close the window
    while (window.isOpen()) {
        // Handle events
        sf::Event event;
        while (window.pollEvent(event)) {
            // Close window button clicked
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Clear screen with a dark blue color
        window.clear(sf::Color(0, 0, 128));

        // draw a box from box2d
        b2Vec2 gravity(0.0f, -10.0f);
        b2World world(gravity);

        b2BodyDef groundBodyDef;
        groundBodyDef.position.Set(0.0f, -10.0f);

        b2Body* groundBody = world.CreateBody(&groundBodyDef);

        b2PolygonShape groundBox;
        groundBox.SetAsBox(50.0f, 10.0f);

        groundBody->CreateFixture(&groundBox, 0.0f);

        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set(0.0f, 4.0f);

        b2Body* body = world.CreateBody(&bodyDef);

        b2PolygonShape dynamicBox;
        dynamicBox.SetAsBox(1.0f, 1.0f);

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &dynamicBox;
        fixtureDef.density = 1.0f;

        body->CreateFixture(&fixtureDef);

        for (int32 i = 0; i < 60; ++i) {
            world.Step(1.0f / 60.0f, 6, 2);

            b2Vec2 position = body->GetPosition();
            float angle = body->GetAngle();

            printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);
        }

        // make the box drawable
        sf::RectangleShape box(sf::Vector2f(50.0f, 50.0f));
        box.setFillColor(sf::Color::Red);
        box.setPosition(0.0f, 0.0f);
        window.draw(box);
        




        // Draw everything here...
        // window.draw(...);

        // End the current frame and display its contents on screen
        window.display();
    }

    return 0;
}
