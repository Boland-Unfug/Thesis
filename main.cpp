#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include "Agent.cpp"
#include "Screen.cpp"
#include "Game.cpp"

#include <iostream>
#include <vector>




int main() {
    Screen screen(800.f, 800.f, "Box2D Test");
    
    // generate 5 agents and put them into a vector
    std::vector<Agent> agents;
    int user_id = 1;

    Agent agent1(user_id, screen.getWorld(), 100.f, 100.f);
    user_id++;
    Agent agent2(user_id, screen.getWorld(), 200.f, 200.f);

    agents.push_back(agent1);
    agents.push_back(agent2);

    agent1.moveAgent(1000.f, 1000.f);
    agent2.moveAgent(-1000.f, -1000.f);

    screen.run(agents);


    return 0;
}