#ifndef AGENT_H
#define AGENT_H

#include <Box2D/Box2D.h>
#include "GameTactics.h"

class Agent {
public:
    Agent(b2Body* body, int id);
    ~Agent();

    void connectAgentToBody();
    signed char doTactic() const {return tactic->doTactic();};

    // Getters
    int getScore();
    int getId();
    b2Body* getBody();
    Agent getAgent() {return *this;};
    GameTactic* getTactic() {return this->tactic;};


    // Setters
    void setScore(int score);
    void setTactic(GameTactic* tactic) {this->tactic = tactic;};

    private:
        int score = 0;
        int id = 0;
        b2Body* body;
        GameTactic* tactic;

};

#endif // AGENT_H