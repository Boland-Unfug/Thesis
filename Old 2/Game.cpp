#include "Game.h"
#include<iostream>

Game::Game() {}

Game::~Game() {}

void Game::play(Agent &agent1, Agent &agent2) {
    //order the players by id for historical reference
    if (agent1.getId() > agent2.getId()) { // Optimize this if necessary
        std::swap(agent1, agent2);
    }
    Pair choices = {agent1.doTactic(), agent2.doTactic()};
    Pair payoffs = getPayoff(choices);
    agent1.setScore(agent1.getScore() + payoffs.first);
    agent2.setScore(agent2.getScore() + payoffs.second);
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
