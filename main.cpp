#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include "Agent.cpp"
#include "Screen.cpp"

#include <iostream>
#include <vector>

int main()
{
    Screen screen(800.f, 800.f, "Box2D Test");
    
    // generate 5 agents and put them into a vector
    std::vector<Agent> agents;
    for (int i = 1; i < 6; i++) {
        Agent agent(i, screen.getWorld(), 100.f * i, 100.f * i);
        agents.push_back(agent);
    }

    // Push the first agent
    agents[0].moveAgent(1000.f, 1000.f);

    screen.run(agents);


    return 0;
}