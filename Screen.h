#ifndef SCREEN_H
#define SCREEN_H

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

class Screen {
public:
    Screen(float world_width, float world_height, const std::string &title);
    void createWall(const b2Vec2& position, const b2Vec2& size);
    void run(std::vector<Agent>); // Main loop for the screen

    //Getters
    float getWorldWidth();
    float getWorldHeight();
    float getFrameRate();
    float getWallThickness();
    b2World& getWorld();
    b2Vec2 getGravity();

    // Setters
    void setWorldWidth(float width);
    void setWorldHeight(float height);
    void setFrameRate(float frameRate);
    void setWallThickness(float thickness);
    void setGravity(b2Vec2 gravity);



private:
    sf::RenderWindow window;
    sf::RectangleShape world_body;
    b2Vec2 gravity = b2Vec2(0.0f, 0.0f);
    b2World world;
    const float SCALE = 30.f;

    float world_width = 800.f;
    float world_height = 800.f;
    const std::string title = "Box2D Test";
    float frameRate = 100.f;
    float wallThickness = 20.f;
    

    // Helper methods
    void handleEvents();
    void update(std::vector<Agent>);
    void render(std::vector<Agent>);



    // ... other private members as needed ...
};

#endif // SCREEN_H
