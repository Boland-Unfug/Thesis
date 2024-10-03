#include <iostream>
#include <vector>
#include <bitset>
#include <unordered_map>
#include <fstream>
#include <string>

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
    - Make program customizable from terminal
        - make the functions more flexible
        - add nodraw option
        - make strategies and maneuvers customizable
    - improve the file writing to store different games
    - add python data analysis
        - add tag array
        - save to a seperate file
        - oh no it converts the data wrong in python
        - try converting to int before storing in file
    - Make the tactic and maneuver initialization process better
        - ensure the same amounts of each agent or at least have that be an option
        - make the code more dense if possible
    - add more game tactics
        - tit for tat
            - I can hand it an array of size [agentnum] full of 0's at instantiation
            - I can then have  it take the agent it is playing and  reference the table for its move
        - tit for two tats
        - naive tit for tat
            - I can have it store just the last move
            - I am going to need a spot to update behaviours after they make their moves
    - make tactics the color
    - add more game maneuvers
        - chase
        - flee
        - move to center
    - make maneuvers the color modification




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

    running into an extremely odd issue while trying to add titfortat
    randomly, the window will not open and the program will just end, which leads me to believe it is a memory issue
    However, I have tracked a possibly different error to the draw function
    So I will remove all randomness first and see if its still happens
    Cause: Titfortat
    probably because I store an array of 0's and ones, and with a lot of those I run into problems


    I  think the current problem is systemic, where I store many things as arrays and that leads to stack overflows
    tomarrow I will work on improving these memory issues, mostly via vectors
    I will also look into improving the pointers vs references and other memory management techniques






    THE DILEMMA:
    two options:
    - every tit for tat stores an array of 0's/1's that stores the last decision of a given agent
    - hardcoding it worked SOB
        - PROBLEM: memory?
    - Every time I call tit for tat, I search through the history to find their last interaction and get the value
        - PROBLEM: exponential time
    - A mix of the two: a matrix that stores the last move between two agents and can be referenced, its a mix of the two and should work well

    Currently it loads everything, but when something happens at round 1001 (gaming) it breaks
    Next goal is to find that

    Also for reducing memory more, now that I have a global history implementing bitshifts should be easier

    I need to literally take everything and find as many ways as possible to reduce their memory.
    One matrix of arrays stores only 0's and 1's - how can I make that more efficient? (bits? pointers?)
    Remove the score array (I can recunstruct it from history later)

    TODO: 10/3/2024
    graphs
        Average
        Individual?
        grouping
    
    Extendibility
        command line args
        game class
        init class

    

    **/

    // Constants
    const int numAgents = 10; // TODO make this dynamic later and also it must be divis by 8 for now
    const unsigned char payoffMatrix[2][2][2] = {
        // accessed via payoffMatrix[choice1][choice2][player]
        {{1, 1}, {5, 0}},
        {{0, 5}, {3, 3}}};

    const float agentRadius = 0.3f;
    const float window_x = 40.0f;
    const float window_y = 30.0f;

    std::cout << "Starting program" << std::endl;

    // Create a rendering engine
    RenderingEngine renderingEngine;

    // Create the main window
    sf::RenderWindow window(sf::VideoMode(window_x * 30, window_y * 30), "SFML window");
    window.setFramerateLimit(120);

    // Create a physics engine
    PhysicsEngine physicsEngine(b2Vec2(0.0f, 0.0f));

    // Create 4 walls
    physicsEngine.CreateWall(b2Vec2(0.f, 0.f), b2Vec2(window_x * 2, 1.f));
    physicsEngine.CreateWall(b2Vec2(0.f, 0.f), b2Vec2(1.f, window_y * 2));
    physicsEngine.CreateWall(b2Vec2(0.f, window_y), b2Vec2(window_x * 2, 1.f));
    physicsEngine.CreateWall(b2Vec2(window_x, 0.f), b2Vec2(1.f, window_y * 2));

    std::cout << "Creating agents" << std::endl;
    // make the vectors of agents
    b2Body *bodies[numAgents]; // array of body pointers
    for (int i = 0; i < numAgents; i++)
    {
        bodies[i] = nullptr;
    }

    // Make the history array
    std::unordered_map<uint64_t, uint8_t> history;
    std::bitset<numAgents> games[numAgents] = {0}; // temporary history LARGE ARRAY
    std::vector<GameManeuver *> maneuvers;         // array of maneuvers
    char maneuverNames[numAgents];                 // array of maneuver names
    for (int i = 0; i < numAgents; i++)
    {
        switch (i % 4)
        {
        case 0:
            maneuvers.push_back(new Up());
            break;
        case 1:
            maneuvers.push_back(new Down());
            break;
        case 2:
            maneuvers.push_back(new Left());
            break;
        case 3:
            maneuvers.push_back(new Right());
            break;
        }
    }

    std::vector<GameTactic *> tactics; // array of tactics
    char tacticNames[numAgents];       // array of tactic names
    for (int i = 0; i < numAgents; i++)
    {
        switch (i % 4)
        {
        case 0:
            tactics.push_back(new Defect());
            tacticNames[i] = 'd';
            break;
        case 1:
            tactics.push_back(new Cooperate());
            tacticNames[i] = 'c';
            break;
        case 2:
            tactics.push_back(new TitForTat());
            tacticNames[i] = 't';
            break;
        case 3:
            tactics.push_back(new NaiveTitForTat());
            tacticNames[i] = 'n';
        }
    }

    std::cout << "Starting game loop" << std::endl;

    // game loop TODO: Go through the whole loop to really make sure it all does what I want
    uint32_t round = 0;
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed || round > numAgents + 1)
            {
                window.close();
            }
        }
        std::cout << "Round: " << round << std::endl;
        // add one agent each round, until the number of agents is reached
        if (round < numAgents)
        {
            bodies[round] = physicsEngine.CreateCircle(round, b2Vec2(1.0f, 1.0f), agentRadius);
            physicsEngine.PushCircle(bodies[round], b2Vec2(1.f, 1.f));
        }

        // LARGE ARRAY
        std::bitset<numAgents> collisions[numAgents] = {0}; // 0 means no collision, 1 means collision

        bool draw = true;
        bool play = true;
        // Update the physics
        b2Contact *contacts = physicsEngine.Step(1.f / 60.f, 8, 3);

        if (round > numAgents && play == true)
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

                    std::printf("Collision between agents %d and %d\n", id1, id2);
                    // Using the round and agent id's, do a series of bitshifts to make the history key
                    uint64_t historyKey = ((uint64_t)round << 32) | ((uint64_t)id1 << 16) | id2;

                    if (tacticNames[id1] == 't')
                    {
                        // std::cout<< "Updating tactic, they played" << choice1 << std::endl;
                        tactics[id1]->updateTactic(id2, games[id2][id1]);
                    }
                    if (tacticNames[id2] == 't')
                    {
                        // std::cout<< "Updating tactic, they played" << choice2 << std::endl;
                        tactics[id2]->updateTactic(id1, games[id1][id2]);
                    }

                    // get the choices from the tactics
                    bool choice1 = tactics[id1]->doTactic(id2);
                    bool choice2 = tactics[id2]->doTactic(id1);



                    // add these to the last game reference array
                    games[id1][id2] = choice2;
                    games[id2][id1] = choice1;

                    // update the tactics but I have to do this before
                    if (tacticNames[id1] == 'n')
                    {
                        // std::cout<< "Updating tactic, they played" << choice1 << std::endl;
                        tactics[id1]->updateTactic(id2, choice2);
                    }
                    if (tacticNames[id2] == 'n')
                    {
                        // std::cout<< "Updating tactic, they played" << choice2 << std::endl;
                        tactics[id2]->updateTactic(id1, choice1);
                    }

                    // Using the two choices, which do either 0 or 1, do a bitshift to make the history value
                    uint8_t gamestate = (choice1) << 1 | choice2;

                    // now we add to the history
                    history[historyKey] = gamestate;
                }
            }

            for (int i = 0; i < numAgents; i++)
            {
                b2Vec2 force = maneuvers[i]->doManeuver();
                physicsEngine.PushCircle(bodies[i], force);
            }
        }
        // update the rendering engine
        if (draw == true)
        {
            renderingEngine.Update(window, bodies, numAgents);
        }

        round += 1;
    }

    std::cout << "Ending program" << std::endl;

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
        MyFile << pair.first << "," << (int)pair.second << std::endl;
    }

    // Close the file
    MyFile.close();

    return 0;
}

