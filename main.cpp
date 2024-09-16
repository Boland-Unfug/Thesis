#include <iostream>
#include <vector>
#include <bitset>
#include <unordered_map>
#include <fstream>

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include "PhysicsEngine.h"
#include "RenderingEngine.h"
#include "GameManeuver.h"
#include "GameManeuvers.h"
#include "GameTactic.h"
#include "GameTactics.h"

int main()
{

    /**
    The rendering should not be a problem, loaded 100000 in ~1 second

    TODO:
    - make the functions more flexible
    - improve the file writing to store different games
    - add python data analysis
    - add more game tactics
        - tit for tat
        - tit for two tats
    - make tactics the color
    - add more game maneuvers
        - chase
        - flee
        - move to center
    - make maneuvers the modification
    - add nodraw


    DONE:
    - set up the physics engine DONE
    - set up the rendering engine DONE
    - set up the game loop DONE
    - set up the bodies and colors DONE
    - render the agents DONE
    - set up the collision detection DONE
    - set up the history unordered map DONE
    - set up the file writing DONEish
    - set up the game maneuvers DONEish
    - set up the game tactics DONEish

    improve the agent creation so there is less overlapping agents (use a feed system) DONE
    Next I need to make it so that agents that go in early don't have an advantage DONE

    make the simple agent? what does it even store? nothing the 'agent' here is the array position

    before I can move the game class, I have to set up collision detection DONE

    Next I have to add game strategies DONE
    I will do this via having an array of strategies that will return a 0 or 1 (betray or cooperate)
    This can then be fed into further game logic
    ? why is a .h instead of .cpp file? I think it is because it is a template class does it need a .cpp file?

    Move over game class Don't Need
    I think instead what I will do is just do it in main and see if that is just so much easier. Might make it
    functions later for easier readability or something but for now this works great

    connect game class to collision Don't need to do this because I am great and it is already DONE :)
    possibly set up listener in main loop? or in physics engine, I could return a list of collisions to main. nope

    Move over history class DONE
    Make history save to a file DONE

    set up maneuvers DONEish
    I can just have it return a b2vec2 of forces to apply store it in its own array
    I will set that array to 0 between, so it only pushes agents once and maybe every 10 rounds or something
    I have them in, but they are not complicated like I want them to be yet

    set up tactics DONEish
    I have them in but they are not complicated yet
    also they don't impact the game yet DONE although I might want to lower the values
    **/

    std::cout << "Starting program" << std::endl;

    // Create a rendering engine
    RenderingEngine renderingEngine;

    // Create the main window
    sf::RenderWindow window(sf::VideoMode(900.0f, 900.0f), "SFML window");
    window.setFramerateLimit(60);

    // Create a physics engine
    PhysicsEngine physicsEngine(b2Vec2(0.0f, 0.0f));

    // Create 4 walls
    physicsEngine.CreateWall(b2Vec2(0.f, 0.f), b2Vec2(60.f, 1.f));
    physicsEngine.CreateWall(b2Vec2(0.f, 0.f), b2Vec2(1.f, 60.f));
    physicsEngine.CreateWall(b2Vec2(0.f, 30.f), b2Vec2(60.f, 1.f));
    physicsEngine.CreateWall(b2Vec2(30.f, 0.f), b2Vec2(1.f, 60.f));

    // Constants
    const int numAgents = 100; // TODO make this dynamic later
    const float agentRadius = 0.5f;
    const unsigned char payoffMatrix[2][2][2] = {
        // accessed via payoffMatrix[choice1][choice2][player]
        {{1, 1}, {5, 0}},
        {{0, 5}, {3, 3}}};
    const int speed_limiter = 1.0f;

    // make the vectors of agents
    b2Body *bodies[numAgents]; // array of body pointers
    for (int i = 0; i < numAgents; i++)
    {
        bodies[i] = nullptr;
    }

    sf::Color colors[numAgents]; // array of colors (I want different colors available

    int scores[numAgents] = {0}; // array of scores very unnecessary, I only care about history but thouroughness ig

    // Make the history array
    std::unordered_map<uint64_t, uint8_t> history;

    GameManeuver *maneuvers[numAgents]; // array of maneuvers
    for (int i = 0; i < numAgents; i++)
    {
        if (i % 6 == 0)
        {
            maneuvers[i] = new Up();
            colors[i] = sf::Color::Red;
        }
        else if (i % 6 == 1)
        {
            maneuvers[i] = new Down();
            colors[i] = sf::Color::Blue;
        }
        else if (i % 6 == 2)
        {
            maneuvers[i] = new Left();
            colors[i] = sf::Color::Green;
        }
        else if (i % 6 == 3)
        {
            maneuvers[i] = new Right();
            colors[i] = sf::Color::Yellow;
        }
        else if (i % 6 == 4)
        {
            maneuvers[i] = new Random();
            colors[i] = sf::Color::White;
        }
        else if (i % 6 == 5)
        {
            maneuvers[i] = new Still();
            colors[i] = sf::Color::White;
            float factor = 1.0f; // 50% of current color
            sf::Uint8 g = static_cast<sf::Uint8>(std::min(255.0f, colors[i].g * factor));
            sf::Uint8 r = static_cast<sf::Uint8>(std::min(255.0f, colors[i].r * factor));
            sf::Uint8 b = static_cast<sf::Uint8>(std::min(255.0f, colors[i].b * factor));
            colors[i] = sf::Color(r, g, b, colors[i].a); // Keep alpha the same
        }
    }

    GameTactic *tactics[numAgents]; // array of tactics
    for (int i = 0; i < numAgents; i++)
    {
        if (i % 8 < 4)
        {
            tactics[i] = new Cooperate();
            float factor = 1.0f; // 50% of current color
            sf::Uint8 g = static_cast<sf::Uint8>(std::min(255.0f, colors[i].g * factor));
            sf::Uint8 r = static_cast<sf::Uint8>(std::min(255.0f, colors[i].r * factor));
            sf::Uint8 b = static_cast<sf::Uint8>(std::min(255.0f, colors[i].b * factor));
            colors[i] = sf::Color(r, g, b, colors[i].a); // Keep alpha the same
        }
        else if (i % 8 >= 4)
        {
            tactics[i] = new Defect();
            float factor = 0.5f; // 100% of current color
            sf::Uint8 g = static_cast<sf::Uint8>(std::min(255.0f, colors[i].g * factor));
            sf::Uint8 r = static_cast<sf::Uint8>(std::min(255.0f, colors[i].r * factor));
            sf::Uint8 b = static_cast<sf::Uint8>(std::min(255.0f, colors[i].b * factor));
            colors[i] = sf::Color(r, g, b, colors[i].a); // Keep alpha the same
        }
    }



    // game loop
    uint32_t round = 0;
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        // add one agent each round, until the number of agents is reached
        if (round < numAgents)
        {
            bodies[round] = physicsEngine.CreateCircle(round, b2Vec2(1.0f, 1.0f), agentRadius);
            physicsEngine.PushCircle(bodies[round], b2Vec2(1.f, 1.f));
        }

        std::bitset<numAgents> collisions[numAgents] = {0}; // 0 means no collision, 1 means collision

        // Update the physics
        b2Contact *contacts = physicsEngine.Step(1.f / 60.f, 8, 3);

        if (round > numAgents)
        {
            for (b2Contact *contact = contacts; contact; contact = contact->GetNext())
            {

                uint16_t id1 = contact->GetFixtureA()->GetBody()->GetUserData().pointer;
                uint16_t id2 = contact->GetFixtureB()->GetBody()->GetUserData().pointer;

                // flip the ids if they are out of order
                if (id1 > id2)
                {
                    uint16_t temp = id1;
                    id1 = id2;
                    id2 = temp;
                }

                if (collisions[id1][id2] == 0)
                { // don't start playing games until all agents exist
                    collisions[id1][id2] = 1;

                    // Using the round and agent id's, do a series of bitshifts to make the history key
                    uint64_t historyKey = ((uint64_t)round << 32) | ((uint64_t)id1 << 16) | id2;

                    // gaming and cooking, these four lines replaced like 50 lines of code
                    bool choice1 = tactics[id1]->doTactic();
                    bool choice2 = tactics[id2]->doTactic();

                    // Using the two choices, which do either 0 or 1, do a bitshift to make the history value
                    uint8_t gamestate = (choice1) << 1 | choice2;

                    // now we add to the history
                    history[historyKey] = gamestate;

                    // std::cin.get();

                    scores[id1] += payoffMatrix[choice1][choice2][0];
                    scores[id2] += payoffMatrix[choice1][choice2][1];
                }
            }

            int round_divisor = 100; // TODO this might be resulting in a 0 force
            if (round % round_divisor == 0)
            {
                for (int i = 0; i < numAgents; i++)
                {
                    b2Vec2 force = maneuvers[i]->doManeuver();
                    force *= (round_divisor * 1 / 100);
                    // will have to check for speed later TODO
                    physicsEngine.PushCircle(bodies[i], force);
                }
            }
        }
        // update the rendering engine
        renderingEngine.Update(window, bodies, colors, numAgents);
        round += 1;
    }


    // TODO: see the files in Data and generate a new name for a file

    
    // if the file exists, delete it
    std::string filename = "../Data/history.csv";

    std::remove(filename.c_str());

    // Create and open a text file
    std::ofstream MyFile(filename);

    // Write to the file
    MyFile << "Key,Value" << std::endl;
    for (const auto &pair : history)
    {
        MyFile << pair.first << "," << pair.second << std::endl;
    }

    // Close the file
    MyFile.close();

    // print out the highest score
    int highestScore = std::max_element(std::begin(scores), std::end(scores)) - std::begin(scores);
    // also get its array position
    std::cout << "Agent " << highestScore << " got " << scores[highestScore] << std::endl;

    return 0;
}