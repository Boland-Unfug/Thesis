// This will contain the game rules and tables
#include "Agent.h"

#ifndef GAME_H
#define GAME_H

struct Set {
// THis will be used to store sets of 4 rounds using bit manipulations to save space
};

struct Pair {
    // I use this for future flexibility and they are stored in the same amount of data as a bool
    // Its compatable with both the payoff matrix and the choices matrix
    signed char first;
    signed char second;
};

    static Pair payoffMatrix[2][2] = { // Will make this variable later, as long as it follows the prisoners dilemma rules
// Cooperate is 0, betray is 1
// The beauty of this is I can access the values extremely flexibly.
// I can find data through a pair of choices, for a single player, as a number using bit shifts, etc
    {{3, 3}, {5, 0}},
    {{0, 5}, {1, 1}}
};

class Game {

    public:
        Game();
        ~Game();

        void play(Agent &agent1, Agent &agent2);

        // Getters
        Pair getPayoff(Pair playerChoices);
        signed char getPayoff(Pair playerChoices, bool player);
        Pair getChoices(Pair playerChoices);
        signed char getChoices(Pair playerChoices, bool player);
};

#endif // GAME_H