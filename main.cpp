#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include <unordered_map>
#include <bitset>
#include <fstream>
#include <filesystem>
#include <iostream>
#include <array>

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

b2Vec2 ApplyAccelerationCap(b2Vec2 force, float accelerationCap)
{
    if (force.Length() > accelerationCap)
    {
        force.Normalize();
        force *= accelerationCap;
    }
    return force;
}

b2Vec2 ApplySpeedCap(b2Vec2 velocity, float speedCap)
{
    
    return velocity;
}

int main()
{
        // constants
    bool tempdraw = true;
    bool tempplay = true;
    // const bool doManeuvers = true; // TODO: implement this
    // const bool doTactics = true; // TODO: implement this
    int tempnumAgents = 1000; // TODO: make this dynamic
    float tempagentRadius = 0.3f;
    int tempmaxRounds = 10000;

    // physics constants
    b2Vec2 tempgravity(0.0f, 0.0f);
    float temptimeStep = 1.0f / 60.0f;
    int32 tempvelocityIterations = 6;
    int32 temppositionIterations = 2;
    float tempdensity = 1.0f;
    float tempfriction = 0.3f;
    float temprestitution = 0.5f;
    b2Vec2 tempstartPosition = b2Vec2(1.0f, 1.0f);
    b2Vec2 tempstartForce = b2Vec2(1.0f, 1.0f);
    float tempspeedCap = 1.0f;
    float tempaccelerationCap = 0.05f;

    // rendering constants
    int tempSCALE = 30.0f;
    int tempwindow_x = 40.0f;
    int tempwindow_y = 30.0f;
    int tempframeRate = 120;

    // read in the constants from the config file
    std::ifstream configInFile("../Configs/settings.csv");

    std::string line;
    // ignore the first line
    std::getline(configInFile, line);
    // Read the file line by line
    while (std::getline(configInFile, line))
    {
        std::stringstream ss(line); // Convert line to a stream for further processing

        // Split the line into comma-separated values
        std::string col1, col2;

        // Get the values from the two columns
        std::getline(ss, col1, ','); // Read first column
        std::getline(ss, col2, ','); // Read second column

        // next steps: convert col 1 to integer?, columns 2 and 3 will associate with an agent maneuver and tactic object type
        // create the agent
        if (col1 == "draw")
        {
            tempdraw = std::stoi(col2);
        }
        else if (col1 == "play")
        {
            tempplay = std::stoi(col2);
        }
        else if (col1 == "numAgents")
        {
            tempnumAgents = std::stoi(col2);
        }
        else if (col1 == "agentRadius")
        {
            tempagentRadius = std::stof(col2);
        }
        else if (col1 == "maxRounds")
        {
            tempmaxRounds = std::stoi(col2);
        }
        else if (col1 == "gravityX")
        {
            tempgravity.x = std::stof(col2);
        }
        else if (col1 == "gravityY")
        {
            tempgravity.y = std::stof(col2);
        }
        else if (col1 == "timeStep")
        {
            temptimeStep = std::stof(col2);
        }
        else if (col1 == "velocityIterations")
        {
            tempvelocityIterations = std::stoi(col2);
        }
        else if (col1 == "positionIterations")
        {
            temppositionIterations = std::stoi(col2);
        }
        else if (col1 == "density")
        {
            tempdensity = std::stof(col2);
        }
        else if (col1 == "friction")
        {
            tempfriction = std::stof(col2);
        }
        else if (col1 == "restitution")
        {
            temprestitution = std::stof(col2);
        }
        else if (col1 == "startPositionX")
        {
            tempstartPosition.x = std::stof(col2);
        }
        else if (col1 == "startPositionY")
        {
            tempstartPosition.y = std::stof(col2);
        }
        else if (col1 == "startForceX")
        {
            tempstartForce.x = std::stof(col2);
        }
        else if (col1 == "startForceY")
        {
            tempstartForce.y = std::stof(col2);
        }
        else if (col1 == "speedCap")
        {
            tempspeedCap = std::stof(col2);
        }
        else if (col1 == "accelerationCap")
        {
            tempaccelerationCap = std::stof(col2);
        }
        else if (col1 == "window_x")
        {
            tempwindow_x = std::stoi(col2);
        }
        else if (col1 == "window_y")
        {
            tempwindow_y = std::stoi(col2);
        }
        else if (col1 == "frameRate")
        {
            tempframeRate = std::stoi(col2);
        }
        else
        {
            std::cerr << "Invalid setting: " << col1 << std::endl;
            return 1;
        }
    }

    configInFile.close(); // Close the file when done

    // game settings
    const bool draw = tempdraw;
    const bool play = tempplay;
    const int numAgents = tempnumAgents;
    const float agentRadius = tempagentRadius;
    const int maxRounds = tempmaxRounds;
    
    // physics settings
    const b2Vec2 gravity(tempgravity.x, tempgravity.y);
    const float timeStep = temptimeStep;
    const int32 velocityIterations = tempvelocityIterations;
    const int32 positionIterations = temppositionIterations;
    const float density = tempdensity;

    const float friction = tempfriction;
    const float restitution = temprestitution;
    const b2Vec2 startPosition(tempstartPosition.x, tempstartPosition.y);
    const b2Vec2 startForce(tempstartForce.x, tempstartForce.y);
    const float speedCap = tempspeedCap;
    const float accelerationCap = tempaccelerationCap;
    
    // rendering settings
    const int SCALE = 30.0f;
    const int window_x = tempwindow_x;
    const int window_y = tempwindow_y;
    const int frameRate = tempframeRate;




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

    // create agents
    b2Body *bodies[numAgents];
    for (int i = 0; i < numAgents; i++)
    {
        bodies[i] = nullptr;
    } // initialize for later trickle effect

    // initialize maneuvers
    std::vector<GameManeuver *> maneuvers;
    std::string maneuverNames[numAgents];

    // initialize tactics
    std::vector<GameTactic *> tactics;
    std::string tacticNames[numAgents];

    // read in the agents
    std::ifstream agentInFile("../Configs/agents.csv");

    // ignore the first line
    std::getline(agentInFile, line);
    // Read the file line by line
    while (std::getline(agentInFile, line))
    {
        std::stringstream ss(line); // Convert line to a stream for further processing

        // Split the line into comma-separated values
        std::string col1, col2, col3;

        // Get the values from the three columns
        std::getline(ss, col1, ','); // Read first column
        std::getline(ss, col2, ','); // Read second column
        std::getline(ss, col3, ','); // Read third column

        // next steps: convert col 1 to integer?, columns 2 and 3 will associate with an agent maneuver and tactic object type
        // create the agent
        int agent = std::stoi(col1);

        // add maneuver to the vector
        if (col2 == "Up")
        {
            maneuvers.push_back(new Up());
        }
        else if (col2 == "Down")
        {
            maneuvers.push_back(new Down());
        }
        else if (col2 == "Left")
        {
            maneuvers.push_back(new Left());
        }
        else if (col2 == "Right")
        {
            maneuvers.push_back(new Right());
        }
        else if (col2 == "Random")
        {
            maneuvers.push_back(new Random());
        }
        else if (col2 == "Still")
        {
            maneuvers.push_back(new Still());
        }
        else if (col2 == "Chase")
        {
            maneuvers.push_back(new Chase());
        }
        else if (col2 == "Flee")
        {
            maneuvers.push_back(new Flee());
        }
        else if (col2 == "WinChase")
        {
            maneuvers.push_back(new WinChase());
        }
        else if (col2 == "LossFlee")
        {
            maneuvers.push_back(new LossFlee());
        }
        else
        {
            std::cerr << "Invalid maneuver type: " << col2 << std::endl;
            return 1;
        }
        maneuverNames[agent] = col2;

        // add tactic to the vector
        if (col3 == "Defect")
        {
            tactics.push_back(new Defect());
        }
        else if (col3 == "Cooperate")
        {
            tactics.push_back(new Cooperate());
        }
        else if (col3 == "TitForTat")
        {
            tactics.push_back(new TitForTat());
        }
        else if (col3 == "NaiveTitForTat")
        {
            tactics.push_back(new NaiveTitForTat());
        }
        else
        {
            std::cerr << "Invalid tactic type: " << col3 << std::endl;
            return 1;
        }
        tacticNames[agent] = col3;
    }

    agentInFile.close(); // Close the file when done

    // Colors
    sf::Color fill[numAgents];
    sf::Color outline[numAgents];

    // read in the colors
    std::ifstream colorInFile("../Configs/colors.csv");

    // ignore the first line
    std::getline(colorInFile, line);
    // Read the file line by line
    while (std::getline(colorInFile, line))
    {
        std::stringstream ss(line); // Convert line to a stream for further processing

        // Split the line into comma-separated values
        std::string col1, col2, col3, col4, col5, col6, col7;

        // Get the values from the three columns
        std::getline(ss, col1, ','); // Read first column
        std::getline(ss, col2, ','); // Read second column
        std::getline(ss, col3, ','); // Read third column
        std::getline(ss, col4, ','); // Read fourth column
        std::getline(ss, col5, ','); // Read fifth column
        std::getline(ss, col6, ','); // Read sixth column
        std::getline(ss, col7, ','); // Read seventh column

        // next steps: convert columns to integers
        //Agent,FillRed,FillGreen,FillBlue,OutlineRed,OutlineGreen,OutlineBlue
        int agent = std::stoi(col1);
        int fillRed = std::stoi(col2);
        int fillGreen = std::stoi(col3);
        int fillBlue = std::stoi(col4);
        int outlineRed = std::stoi(col5);
        int outlineGreen = std::stoi(col6);
        int outlineBlue = std::stoi(col7);
        
        // add the colors
        fill[agent] = sf::Color(std::stoi(col2), std::stoi(col3), std::stoi(col4));
        outline[agent] = sf::Color(std::stoi(col5), std::stoi(col6), std::stoi(col7));
    }

    // create history
    std::unordered_map<uint64_t, uint8_t> history;
    std::vector<std::vector<bool>> games(numAgents, std::vector<bool>(numAgents, 0)); // Stores in the form of games[agent1][agent2]

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
                std::vector<std::vector<bool>> collisions(numAgents, std::vector<bool>(numAgents, 0));
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
                        if (tacticNames[id1].compare("TitForTat") == 1)
                        {
                            tactics[id1]->updateTactic(games[id1][id2]);
                        }
                        if (tacticNames[id1].compare("TitForTat") == 1)
                        {
                            tactics[id1]->updateTactic(games[id2][id1]);
                        }

                        // this constitutes playing the game
                        bool choice1 = tactics[id1]->doTactic();
                        bool choice2 = tactics[id2]->doTactic();

                        // add the game for future tit for tat checks
                        games[id1][id2] = choice1;
                        games[id2][id1] = choice2;

                        if (tacticNames[id1].compare("NaiveTitForTat") == 1)
                        {
                            tactics[id1]->updateTactic(games[id1][id2]);
                        }
                        if (tacticNames[id1].compare("NaiveTitForTat") == 1)
                        {
                            tactics[id1]->updateTactic(games[id2][id1]);
                        }

                        b2Vec2 contactPoint = worldManifold.points[0]; // I can do this because they are all circles

                        maneuvers[id1]->updateManeuver(contactPoint, bodyA->GetPosition());
                        maneuvers[id2]->updateManeuver(contactPoint, bodyB->GetPosition());
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

                // do the maneuvers
                for (int i = 0; i < numAgents; i++) // going to test agents moving each round first
                {
                    b2Vec2 force = maneuvers[i]->doManeuver();

                    // Acceleration cap
                    force = ApplyAccelerationCap(force, accelerationCap);

                    // Speed cap
                    bodies[i]->SetLinearVelocity(ApplySpeedCap(bodies[i]->GetLinearVelocity(), speedCap));

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
    historyFile << "Key,Value" << std::endl;
    for (const auto &pair : history)
    {
        historyFile << pair.first << "," << (int)pair.second << std::endl;
    }

    // write the agents
    agentFile << "Agent, Maneuver,Fill, Tactic, Outline" << std::endl;
    for (int i = 0; i < numAgents; i++)
    {
        agentFile << i << "," << maneuverNames[i] << "," << fill[i].toInteger() << "," << tacticNames[i] << "," << outline[i].toInteger() << std::endl;
    }

    // write the games
    gameFile << "Setting, Value" << std::endl;
    gameFile << "draw, " << draw << std::endl;
    gameFile << "play, " << play << std::endl;
    gameFile << "numAgents, " << numAgents << std::endl;
    gameFile << "agentRadius, " << agentRadius << std::endl;
    gameFile << "maxrounds," << maxRounds << std::endl;
    gameFile << "gravityX, " << gravity.x << std::endl;
    gameFile << "gravityY, " << gravity.y << std::endl;
    gameFile << "timeStep, " << timeStep << std::endl;
    gameFile << "velocityIterations, " << velocityIterations << std::endl;
    gameFile << "positionIterations, " << positionIterations << std::endl;
    gameFile << "density, " << density << std::endl;
    gameFile << "friction, " << friction << std::endl;
    gameFile << "restitution, " << restitution << std::endl;
    gameFile << "startPositionX, " << startPosition.x << std::endl;
    gameFile << "startPositionY, " << startPosition.y << std::endl;
    gameFile << "startForceX, " << startForce.x << std::endl;
    gameFile << "startForceY, " << startForce.y << std::endl;
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