#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include <unordered_map>
#include <bitset>
#include <fstream>
#include <filesystem>

#include "GameManeuvers.h"
#include "GameTactics.h"

b2Body *CreateWall(b2World *world, const b2Vec2 &position, const b2Vec2 &size)
{
    // Hand this meters, not pixels (divide by 30)
    b2BodyDef bodyDef;
    bodyDef.position = position;
    b2Body *body = world->CreateBody(&bodyDef);

    b2PolygonShape box;
    box.SetAsBox(size.x / 2, size.y / 2);

    body->CreateFixture(&box, 0.0f);

    return body;
}

b2Body *CreateCircle(b2World *world, int id, const b2Vec2 &position, float radius, float density, float friction, float restitution)
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = position;
    uintptr_t pointer = (uintptr_t)id;
    bodyDef.userData.pointer = pointer;
    b2Body *body = world->CreateBody(&bodyDef);

    b2CircleShape circle;
    circle.m_radius = radius;

    b2FixtureDef fixtureDef; // define the fixture, which defines the physics to apply to the body
    fixtureDef.shape = &circle;
    fixtureDef.density = density;
    fixtureDef.friction = friction;
    fixtureDef.restitution = restitution;

    body->CreateFixture(&fixtureDef);

    return body;
}

int main()
{

    // constants
    const bool draw = true;
    const bool play = true;
    // const bool doManeuvers = true; // TODO: implement this
    // const bool doTactics = true; // TODO: implement this
    const int numAgents = 1000; // TODO: make this dynamic
    const float agentRadius = 0.3f;
    const int maxRounds = 10000;

    // physics constants
    const b2Vec2 gravity(0.0f, 0.0f);
    const float timeStep = 1.0f / 60.0f;
    const int32 velocityIterations = 6;
    const int32 positionIterations = 2;
    const float density = 1.0f;
    const float friction = 0.3f;
    const float restitution = 0.5f;
    const b2Vec2 startPosition = b2Vec2(1.0f, 1.0f);
    const b2Vec2 startForce = b2Vec2(1.0f, 1.0f);
    const float speedCap = 1.0f;
    const float accelerationCap = 0.05f;

    // rendering constants
    const int SCALE = 30.0f;
    const int window_x = 40.0f;
    const int window_y = 30.0f;
    const int frameRate = 120;

    // game constants
    const unsigned char payoffMatrix[2][2][2] = {
        // accessed via payoffMatrix[choice1][choice2][player]
        // 0 = cooperate, 1 = defect
        {{3, 3}, {0, 5}},
        {{5, 0}, {1, 1}}};

    // initialization

    sf::RenderWindow window(sf::VideoMode(window_x * SCALE, window_y * SCALE), "SFML window");
    window.setFramerateLimit(frameRate);

    b2World *world = new b2World(gravity);

    // create walls
    CreateWall(world, b2Vec2(0.0f, 0.0f), b2Vec2(window_x * 2, 1.0f));
    CreateWall(world, b2Vec2(0.0f, 0.0f), b2Vec2(1.0f, window_y * 2));
    CreateWall(world, b2Vec2(0.0f, window_y), b2Vec2(window_x * 2, 1.0f));
    CreateWall(world, b2Vec2(window_x, 0.0f), b2Vec2(1.0f, window_y * 2));

    // Colors
    sf::Color fill[numAgents];
    sf::Color outline[numAgents];

    // create agents
    b2Body *bodies[numAgents];
    for (int i = 0; i < numAgents; i++)
    {
        bodies[i] = nullptr;
    } // initialize for later trickle effect

    // create maneuvers
    std::vector<GameManeuver *> maneuvers;
    char maneuverNames[numAgents];
    for (int i = 0; i < numAgents; i++)
    {
        switch (i % 2)
        {
        case 0:
            maneuvers.push_back(new Chase());
            maneuverNames[i] = 'c';
            fill[i] = sf::Color::Magenta;
            break;
        case 1:
            maneuvers.push_back(new Flee());
            maneuverNames[i] = 'f';
            fill[i] = sf::Color::Cyan;
            break;
        }
    }

    // create tactics
    std::vector<GameTactic *> tactics;
    char tacticNames[numAgents];
    for (int i = 0; i < numAgents; i++)
    {
        switch (i % 3)
        {
        case 0:
            tactics.push_back(new Defect());
            tacticNames[i] = 'd';
            outline[i] = sf::Color::Red;
            break;
        case 1:
            tactics.push_back(new Cooperate());
            tacticNames[i] = 'c';
            outline[i] = sf::Color::Green;
            break;
        case 2:
            tactics.push_back(new TitForTat());
            tacticNames[i] = 't';
            outline[i] = sf::Color::Blue;
            break;
        }
    }

    // create history
    std::unordered_map<uint64_t, uint8_t> history;
    std::bitset<numAgents> games[numAgents] = {0}; // TODO: this gives me the ick but is necessary for tit for tat agents

    // game loop
    uint32_t round = 0;
    bool paused = false;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Space)
                {
                    paused = !paused;
                }
            }
        }

        if (paused == false)
        {

            world->Step(timeStep, velocityIterations, positionIterations);

            if (round < numAgents) // trickle effect
            {
                bodies[round] = CreateCircle(world, round, startPosition, agentRadius, density, friction, restitution);
                bodies[round]->ApplyLinearImpulse(startForce, bodies[round]->GetWorldCenter(), true);
            }

            if (play == true && round > numAgents) // needed for the trickle effect to not bias results
            {

                std::bitset<numAgents> collisions[numAgents] = {0}; // 0 means no collision, 1 means collision
                b2Contact *contact = world->GetContactList();       // Get the head of the contact list

                while (contact != nullptr)
                {
                    b2Fixture *fixtureA = contact->GetFixtureA();
                    b2Fixture *fixtureB = contact->GetFixtureB();
                    b2Body *bodyA = fixtureA->GetBody();
                    b2Body *bodyB = fixtureB->GetBody();
                    uint16_t id1 = bodyA->GetUserData().pointer;
                    uint16_t id2 = bodyB->GetUserData().pointer;

                    // Check if the contact is actually enabled (true collision) and not already played
                    if (collisions[id1][id2] == 0 && contact->IsTouching())
                    {
                        // add the collision to the list
                        collisions[id1][id2] = 1;
                        // Access the contact manifold to get the contact points
                        b2WorldManifold worldManifold;
                        contact->GetWorldManifold(&worldManifold);

                        // tactic logic

                        // start by updating tit for tat
                        if (tacticNames[id1] == 't')
                        {
                            tactics[id1]->updateTactic(id2, games[id2][id1]);
                        }
                        if (tacticNames[id2] == 't')
                        {
                            tactics[id2]->updateTactic(id1, games[id1][id2]);
                        }

                        // this constitutes playing the game
                        bool choice1 = tactics[id1]->doTactic(id2);
                        bool choice2 = tactics[id2]->doTactic(id1);

                        // add the game for future tit for tat checks
                        games[id1][id2] = choice2;
                        games[id2][id1] = choice1;

                        // update naive tit for tat
                        if (tacticNames[id1] == 'n')
                        {
                            tactics[id1]->updateTactic(id2, choice2);
                        }
                        if (tacticNames[id2] == 'n')
                        {
                            tactics[id2]->updateTactic(id1, choice1);
                        }

                        b2Vec2 contactPoint = worldManifold.points[0]; // I can do this because they are all circles

                        if (maneuverNames[id1] == 'f' || maneuverNames[id1] == 'c')
                        {
                            maneuvers[id1]->updateManeuver(contactPoint, bodyA->GetPosition());
                        };
                        if (maneuverNames[id2] == 'f' || maneuverNames[id2] == 'c')
                        {
                            maneuvers[id2]->updateManeuver(contactPoint, bodyB->GetPosition());
                        };
                        if (maneuverNames[id1] == 'w' || maneuverNames[id1] == 'l')
                        {
                            if (choice1 == 1 && choice2 == 0 || choice1 == 0 && choice2 == 0)
                            {
                                maneuvers[id1]->updateManeuver(contactPoint, bodyA->GetPosition());
                            }
                        };
                        if (maneuverNames[id2] == 'W' || maneuverNames[id2] == 'L')
                        {
                            if (choice1 == 0 && choice2 == 1 || choice1 == 0 && choice2 == 0)
                            {
                                maneuvers[id2]->updateManeuver(contactPoint, bodyB->GetPosition());
                            }
                        };
                        // update the history
                        // to save memory, we garuntee agent1 < agent2
                        if (id1 > id2)
                        {
                            uint16_t temp = id1;
                            id1 = id2;
                            id2 = temp;
                            bool tempChoice = choice1;
                            choice1 = choice2;
                            choice2 = tempChoice;
                        }
                        uint64_t historyKey = ((uint64_t)round << 32) | ((uint64_t)id1 << 16) | id2;
                        uint8_t gamestate = (choice1) << 1 | choice2;
                        history[historyKey] = gamestate;
                    }

                    // Move to the next contact in the list
                    contact = contact->GetNext();
                }

                for (int i = 0; i < numAgents; i++) // going to test agents moving each round first
                {
                    b2Vec2 force = maneuvers[i]->doManeuver();

                    // Acceleration cap
                    if (force.x > accelerationCap)
                    {
                        force.x = accelerationCap;
                    }
                    if (force.y > accelerationCap)
                    {
                        force.y = accelerationCap;
                    }
                    if (force.x < -accelerationCap)
                    {
                        force.x = -accelerationCap;
                    }
                    if (force.y < -accelerationCap)
                    {
                        force.y = -accelerationCap;
                    }

                    // Speed cap
                    if (bodies[i]->GetLinearVelocity().x > speedCap)
                    {
                        bodies[i]->SetLinearVelocity(b2Vec2(speedCap, bodies[i]->GetLinearVelocity().y));
                    }
                    if (bodies[i]->GetLinearVelocity().y > speedCap)
                    {
                        bodies[i]->SetLinearVelocity(b2Vec2(bodies[i]->GetLinearVelocity().x, speedCap));
                    }
                    if (bodies[i]->GetLinearVelocity().x < -speedCap)
                    {
                        bodies[i]->SetLinearVelocity(b2Vec2(-speedCap, bodies[i]->GetLinearVelocity().y));
                    }
                    if (bodies[i]->GetLinearVelocity().y < -speedCap)
                    {
                        bodies[i]->SetLinearVelocity(b2Vec2(bodies[i]->GetLinearVelocity().x, -speedCap));
                    }

                    bodies[i]->ApplyLinearImpulse(force, bodies[i]->GetWorldCenter(), true);
                }
            }

            if (draw == true)
            {
                // draw the agents
                window.clear();
                for (int i = 0; i < numAgents; i++)
                {
                    if (bodies[i] != nullptr)
                    {
                        b2Fixture *fixture = bodies[i]->GetFixtureList();
                        b2CircleShape *circleShape = static_cast<b2CircleShape *>(fixture->GetShape());
                        float radius = circleShape->m_radius;

                        sf::CircleShape circle(radius * SCALE);
                        circle.setOrigin(radius * SCALE, radius * SCALE);
                        circle.setPosition(SCALE * bodies[i]->GetPosition().x, SCALE * bodies[i]->GetPosition().y);
                        circle.setRotation(bodies[i]->GetAngle() * 180.0f / b2_pi);

                        circle.setFillColor(fill[i]);
                        circle.setOutlineThickness(-(radius / 3 * SCALE));
                        circle.setOutlineColor(outline[i]);
                        window.draw(circle);
                    }; // lets me do the feed in effect
                }
                window.display();
            }
                    round++;
        }
    }

    // save the data in 3 files
    // get the file count in Data
    auto dirIter = std::filesystem::directory_iterator("../Data");
    int fileCount = 0;

    for (auto &entry : dirIter)
    {
        if (entry.is_regular_file())
        {
            ++fileCount;
        }
    }
    fileCount = fileCount / 3;

    // name the files
    std::string historydata = "../Data/historydata " + std::to_string(fileCount) + ".csv";
    std::string agentdata = "../Data/agentdata " + std::to_string(fileCount) + ".csv";
    std::string gamedata = "../Data/gamedata " + std::to_string(fileCount) + ".csv";

    // Create the files
    std::ofstream historyFile(historydata);
    std::ofstream agentFile(agentdata);
    std::ofstream gameFile(gamedata);

    // write the history
    historyFile << "Key, Value" << std::endl;
    for (const auto &pair : history)
    {
        historyFile << pair.first << "," << (int)pair.second << std::endl;
    }

    // write the agents
    agentFile << "Agent, Maneuver, Tactic" << std::endl;
    for (int i = 0; i < numAgents; i++)
    {
        agentFile << i << "," << maneuverNames[i] << "," << tacticNames[i] << std::endl;
    }

    // write the games
    gameFile << "Setting, Value" << std::endl;
    gameFile << "draw, " << draw << std::endl;
    gameFile << "play, " << play << std::endl;
    gameFile << "numAgents, " << numAgents << std::endl;
    gameFile << "agentRadius, " << agentRadius << std::endl;
    gameFile << "maxrounds," << maxRounds <<std::endl;
    gameFile << "gravity, " << gravity.x << "," << gravity.y << std::endl;
    gameFile << "timeStep, " << timeStep << std::endl;
    gameFile << "velocityIterations, " << velocityIterations << std::endl;
    gameFile << "positionIterations, " << positionIterations << std::endl;
    gameFile << "density, " << density << std::endl;
    gameFile << "friction, " << friction << std::endl;
    gameFile << "restitution, " << restitution << std::endl;
    gameFile << "startPosition, " << startPosition.x << "," << startPosition.y << std::endl;
    gameFile << "starForce, " << startForce.x << "," << startForce.y << std::endl;
    gameFile << "speedCap, " << speedCap << std::endl;
    gameFile << "accelerationCap, " << accelerationCap << std::endl;
    gameFile << "SCALE, " << SCALE << std::endl;
    gameFile << "window_x, " << window_x << std::endl;
    gameFile << "window_y, " << window_y << std::endl;
    gameFile << "frameRate, " << frameRate << std::endl;

    // close the files
    historyFile.close();
    agentFile.close();
    gameFile.close();

    return 0;
}