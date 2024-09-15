#include "Game.h"
#include<iostream>

Game::Game() {}

Game::~Game() {}

void Game::play(Agent &agent1, Agent &agent2) {
    // std::cout << "Playing game between agents " << agent1.getId() << " and " << agent2.getId() << std::endl;
    //order the players by id for historical reference
    if (agent1.getId() > agent2.getId()) { // Optimize this if necessary
        std::swap(agent1, agent2);
    }
    Pair choices = {agent1.doTactic(), agent2.doTactic()};
    // std::cout << "Agent " << agent1.getId() << " chose " << (int)choices.first << std::endl;
    // std::cout << "Agent " << agent2.getId() << " chose " << (int)choices.second << std::endl;
    Pair payoffs = getPayoff(choices);
    // std::cout << "Agent " << agent1.getId() << " got " << (int)payoffs.first << " points" << std::endl;
    // std::cout << "Agent " << agent2.getId() << " got " << (int)payoffs.second << " points" << std::endl;
    agent1.setScore(agent1.getScore() + payoffs.first);
    agent2.setScore(agent2.getScore() + payoffs.second);
    // std::cout << "Agent " << agent1.getId() << " now has " << agent1.getScore() << " points" << std::endl;
    // std::cout << "Agent " << agent2.getId() << " now has " << agent2.getScore() << " points" << std::endl;
}

Pair Game::getPayoff(Pair playerChoices) {
    return payoffMatrix[playerChoices.first][playerChoices.second];
}

signed char Game::getPayoff(Pair playerChoices, bool player) {
    if (player == 0) {
        return payoffMatrix[playerChoices.first][playerChoices.second].first;
    } else if (player == 1) {
        return payoffMatrix[playerChoices.first][playerChoices.second].second;
    } else {
        return -1;
    }
}

Pair Game::getChoices(Pair playerChoices) {
    return playerChoices;
}

signed char Game::getChoices(Pair playerChoices, bool player) {
    if (player == 0) {
        return playerChoices.first;
    } else if (player == 1) {
        return playerChoices.second;
    } else {
        return -1;
    }
}
