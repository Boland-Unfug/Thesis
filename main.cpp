#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

int main()
{
    // Window setup using SFML
    sf::RenderWindow window(sf::VideoMode(800, 600), "Box2D and SFML Demo");

    // Define the gravity vector.
    b2Vec2 gravity(0.0f, 9.8f);

    // Construct a world object.
    b2World world(gravity);

    // SCALE factor to convert between Box2D units (meters) and pixels.
    const float SCALE = 30.f;

    // Create ground body
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(400.0f / SCALE, 500.0f / SCALE);
    b2Body* groundBody = world.CreateBody(&groundBodyDef);
    b2PolygonShape groundBox;
    groundBox.SetAsBox(250.0f / SCALE, 10.0f / SCALE);
    groundBody->CreateFixture(&groundBox, 0.0f);

    // Create dynamic body
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(400.0f / SCALE, 100.0f / SCALE);
    b2Body* body = world.CreateBody(&bodyDef);
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(30.0f / SCALE, 30.0f / SCALE);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    body->CreateFixture(&fixtureDef);

    // SFML shape for the box
    sf::RectangleShape box(sf::Vector2f(60.0f, 60.0f));
    box.setFillColor(sf::Color::Red);
    box.setOrigin(30.f, 30.f);

    // SFML shape for the ground
    sf::RectangleShape ground(sf::Vector2f(500.0f, 20.0f));
    ground.setFillColor(sf::Color::Green);
    ground.setPosition(400.f, 500.f);
    ground.setOrigin(250.f, 10.f);

    while (window.isOpen())
    {
        // Handle window events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Step the physics world
        world.Step(1/60.f, 6, 2);

        // Update box position and rotation
        b2Vec2 position = body->GetPosition();
        float angle = body->GetAngle();
        box.setPosition(position.x * SCALE, position.y * SCALE);
        box.setRotation(angle * 180.0f / b2_pi);

        // Clear window
        window.clear();

        // Draw ground and box
        window.draw(ground);
        window.draw(box);

        // Display
        window.display();
    }

    return 0;
}
