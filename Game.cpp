#include "Game.h"

Game::Game() {}

Game::~Game() {}

State Game::hash(Pair playerChoices) {
    State state;
    state.state = playerChoices.first << 1 | playerChoices.second; // I feel like this will not be right
    return state;
}

Pair Game::dehash(State state) {
    Pair playerChoices;
    playerChoices.first = state.state >> 1;
    playerChoices.second = state.state & 1;
    return playerChoices;
}

Pair Game::getPayoff(Pair playerChoices) {
    State state = hash(playerChoices);
    return payoffMatrix[state.state];
}

Pair Game::getPayoff(int state) {
    return payoffMatrix[state];
}

void Game::play(Agent &agent1, Agent &agent2) {
    Pair playerChoices;
    playerChoices.first = 0;
    playerChoices.second = 1;

    Pair payoff = getPayoff(playerChoices);

    agent1.setScore(payoff.first);
    agent2.setScore(payoff.second);
}

// Path: Agent.h