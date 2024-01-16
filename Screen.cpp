#include "Screen.h"


Screen::Screen(float world_width, float world_height, const std::string &title) 
    : window(sf::VideoMode(world_width, world_height), title), world(gravity) {

    // create the window
    window.setFramerateLimit(frameRate);

    // Create the world body
    world_body.setSize(sf::Vector2f(world_width, world_height));
    world_body.setFillColor(sf::Color::Black);
    world_body.setOrigin(world_body.getSize().x / 2, world_body.getSize().y / 2);
    world_body.setPosition(world_width / 2, world_height / 2);


    // Create walls
    createWall(b2Vec2(world_width / 2 / SCALE, 0), b2Vec2(world_width / SCALE, 1)); // Top
    createWall(b2Vec2(world_width / 2 / SCALE, world_height / SCALE), b2Vec2(world_width / SCALE, 1)); // Bottom
    createWall(b2Vec2(0, world_height / 2 / SCALE), b2Vec2(1, world_height / SCALE)); // Left
    createWall(b2Vec2(world_width / SCALE, world_height / 2 / SCALE), b2Vec2(1, world_height / SCALE)); // Right
}

void Screen::createWall(const b2Vec2& position, const b2Vec2& size) {
    b2BodyDef bodyDef;
    bodyDef.position = position;
    b2Body* wall = world.CreateBody(&bodyDef);

    b2PolygonShape box;
    box.SetAsBox(size.x / 2, size.y / 2);

    wall->CreateFixture(&box, 0.0f); // Zero density makes it static
}

void Screen::run(std::vector<Agent> agents) {
    while (window.isOpen()) {
        handleEvents();
        update(agents);
        render(agents);
    }
}

void Screen::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
    }
}

void Screen::update(std::vector<Agent> agents) {
    // Update the Box2D world and other elements
    world.Step(1 / frameRate, 8, 3);
}

void Screen::render(std::vector<Agent> agents) {
    window.clear();
    // Draw elements here
    window.draw(world_body);

    // Draw the walls
    sf::RectangleShape topWall(sf::Vector2f(world_width, wallThickness));
    topWall.setFillColor(sf::Color::Red);
    topWall.setPosition(0, 0);
    window.draw(topWall);

    sf::RectangleShape bottomWall(sf::Vector2f(world_width, wallThickness));
    bottomWall.setFillColor(sf::Color::Blue);
    bottomWall.setPosition(0, world_height - wallThickness);
    window.draw(bottomWall);

    sf::RectangleShape leftWall(sf::Vector2f(wallThickness, world_height));
    leftWall.setFillColor(sf::Color::Green);
    leftWall.setPosition(0, 0);
    window.draw(leftWall);

    sf::RectangleShape rightWall(sf::Vector2f(wallThickness, world_height));
    rightWall.setPosition(world_width - wallThickness, 0);
    rightWall.setFillColor(sf::Color::Yellow);
    window.draw(rightWall);

    // Draw the agents
    for (Agent agent : agents) {
        agent.drawAgent(window);
    }

    window.display();
}


// Getters

float Screen::getWorldWidth() {
    return world_width;
}

float Screen::getWorldHeight() {
    return world_height;
}

float Screen::getFrameRate() {
    return frameRate;
}

float Screen::getWallThickness() {
    return wallThickness;
}

b2World& Screen::getWorld() {
    return world;
}

b2Vec2 Screen::getGravity() {
    return gravity;
}

// Setters

void Screen::setWorldWidth(float width) {
    world_width = width;
}

void Screen::setWorldHeight(float height) {
    world_height = height;
}

void Screen::setFrameRate(float frameRate) {
    this->frameRate = frameRate;
}

void Screen::setWallThickness(float thickness) {
    wallThickness = thickness;
}

void Screen::setGravity(b2Vec2 gravity) {
    this->gravity = gravity;
}

