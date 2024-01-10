#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

int main()
{
    // Window setup using SFML
    float size = 800.f;
    sf::RenderWindow window(sf::VideoMode(size, size), "Box2D and SFML Demo");
    window.setFramerateLimit(100);

    // Define the gravity vector.
    b2Vec2 gravity(0.0f, 0.0f);

    // Construct a world object.
    b2World world(gravity);

    // SCALE factor to convert between Box2D units (meters) and pixels.
    const float SCALE = 30.f;

    // Create ground body
    float ground_x_position = 400.f; // needs to be the middle, as things are measured from the center
    float ground_y_position = 800.f;
    float ground_width = size; // If we divide these by two we get the center of the rectangle
    float ground_height = 20.f;
    // These numbers get modified by their CENTER, not the top left corner
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(ground_x_position / SCALE, ground_y_position / SCALE);
    b2Body* groundBody = world.CreateBody(&groundBodyDef);
    b2PolygonShape groundBox;
    groundBox.SetAsBox((ground_width/2) / SCALE, (ground_height/2) / SCALE);
    groundBody->CreateFixture(&groundBox, 0.0f);

    // SFML shape for the ground
    sf::RectangleShape ground(sf::Vector2f(ground_width, ground_height));
    ground.setFillColor(sf::Color::Green);
    ground.setPosition(ground_x_position, ground_y_position);
    ground.setOrigin(ground_width/2, ground_height/2); // relative to the 500 x 20 rectangle, so this is in the middle?

    // Create ceiling body
    float ceiling_x_position = 400.f; // needs to be the middle, as things are measured from the center
    float ceiling_y_position = 0.f;
    float ceiling_width = size; // If we divide these by two we get the center of the rectangle
    float ceiling_height = 20.f;
    // These numbers get modified by their CENTER, not the top left corner
    b2BodyDef ceilingBodyDef;
    ceilingBodyDef.position.Set(ceiling_x_position / SCALE, ceiling_y_position / SCALE);
    b2Body* ceilingBody = world.CreateBody(&ceilingBodyDef);
    b2PolygonShape ceilingBox;
    ceilingBox.SetAsBox((ceiling_width/2) / SCALE, (ceiling_height/2) / SCALE);
    ceilingBody->CreateFixture(&ceilingBox, 0.0f);

    // SFML shape for the ceiling
    sf::RectangleShape ceiling(sf::Vector2f(ceiling_width, ceiling_height));
    ceiling.setFillColor(sf::Color::Green);
    ceiling.setPosition(ceiling_x_position, ceiling_y_position);
    ceiling.setOrigin(ceiling_width/2, ceiling_height/2); // relative to the 500 x 20 rectangle, so this is in the middle?

    // Create left wall body
    float left_wall_x_position = 0.f; // needs to be the middle, as things are measured from the center
    float left_wall_y_position = 400.f;
    float left_wall_width = 20.f; // If we divide these by two we get the center of the rectangle
    float left_wall_height = size; // If we divide these by two we get the center of the rectangle
    // These numbers get modified by their CENTER, not the top left corner
    b2BodyDef left_wallBodyDef;
    left_wallBodyDef.position.Set(left_wall_x_position / SCALE, left_wall_y_position / SCALE);
    b2Body* left_wallBody = world.CreateBody(&left_wallBodyDef);
    b2PolygonShape left_wallBox;
    left_wallBox.SetAsBox((left_wall_width/2) / SCALE, (left_wall_height/2) / SCALE);
    left_wallBody->CreateFixture(&left_wallBox, 0.0f);

    // SFML shape for the left wall
    sf::RectangleShape left_wall(sf::Vector2f(left_wall_width, left_wall_height));
    left_wall.setFillColor(sf::Color::Green);
    left_wall.setPosition(left_wall_x_position, left_wall_y_position);
    left_wall.setOrigin(left_wall_width/2, left_wall_height/2); // relative to the 500 x 20 rectangle, so this is in the middle?

    // Create right wall body
    float right_wall_x_position = 800.f; // needs to be the middle, as things are measured from the center
    float right_wall_y_position = 400.f;
    float right_wall_width = 20.f; // If we divide these by two we get the center of the rectangle
    float right_wall_height = size; // If we divide these by two we get the center of the rectangle
    // These numbers get modified by their CENTER, not the top left corner
    b2BodyDef right_wallBodyDef;
    right_wallBodyDef.position.Set(right_wall_x_position / SCALE, right_wall_y_position / SCALE);
    b2Body* right_wallBody = world.CreateBody(&right_wallBodyDef);
    b2PolygonShape right_wallBox;
    right_wallBox.SetAsBox((right_wall_width/2) / SCALE, (right_wall_height/2) / SCALE);
    right_wallBody->CreateFixture(&right_wallBox, 0.0f);

    // SFML shape for the right wall
    sf::RectangleShape right_wall(sf::Vector2f(right_wall_width, right_wall_height));
    right_wall.setFillColor(sf::Color::Green);
    right_wall.setPosition(right_wall_x_position, right_wall_y_position);
    right_wall.setOrigin(right_wall_width/2, right_wall_height/2); // relative to the 500 x 20 rectangle, so this is in the middle?

    // Create dynamic body
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(400.0f / SCALE, 100.0f / SCALE);
    b2Body* body = world.CreateBody(&bodyDef);
    b2CircleShape dynamicCircle;
    dynamicCircle.m_radius = 30.0f / SCALE;
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicCircle;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.0f;
    fixtureDef.restitution = 0.9f;
    body->CreateFixture(&fixtureDef);

    // Apply right force
    b2Vec2 impulse(10.0f, 5.0f);
    body->ApplyLinearImpulse(impulse, body->GetWorldCenter(), true);

    // SFML shape for the box
    sf::CircleShape box(30.f);
    box.setFillColor(sf::Color::Red);
    box.setOrigin(30.f, 30.f);

    // Create another dynamic body
    b2BodyDef bodyDef2;
    bodyDef2.type = b2_dynamicBody;
    bodyDef2.position.Set(400.0f / SCALE, 100.0f / SCALE);
    b2Body* body2 = world.CreateBody(&bodyDef2);
    b2CircleShape dynamicCircle2;
    dynamicCircle2.m_radius = 30.0f / SCALE;
    b2FixtureDef fixtureDef2;
    fixtureDef2.shape = &dynamicCircle2;
    fixtureDef2.density = 1.0f;
    fixtureDef2.friction = 0.0f;
    fixtureDef2.restitution = 0.9f;
    body2->CreateFixture(&fixtureDef2);

    // Apply left force
    b2Vec2 impulse2(10.0f, 10.0f);
    body2->ApplyLinearImpulse(impulse2, body2->GetWorldCenter(), true);

    // SFML shape for the box
    sf::CircleShape box2(30.f);
    box2.setFillColor(sf::Color::Blue);
    box2.setOrigin(30.f, 30.f);


    

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
        window.draw(box2);
        window.draw(ceiling);
        window.draw(left_wall);
        window.draw(right_wall);

        // Display
        window.display();
    }

    return 0;
}
