// This will contain the game rules and tables
#include "Agent.h"

#ifndef GAME_H
#define GAME_H

struct State {
    unsigned char state : 2;
};

struct Pair {
    unsigned char first;
    unsigned char second;
};

const Pair payoffMatrix[4] = {{3,3}, {0,5}, {5,0}, {1,1}};

class Game {
    public:
        Game();
        ~Game();
        State hash(Pair playerChoices);
        Pair dehash(State state);
        Pair getPayoff(Pair playerChoices);
        Pair getPayoff(int state);

        void play(Agent &agent1, Agent &agent2);
};

#endif // GAME_H