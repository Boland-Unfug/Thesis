#ifndef AGENT_H
#define AGENT_H

#include <Box2D/Box2D.h>
#include "GameTactics.h"

class Agent {
public:
    Agent(b2Body* body, int id);
    ~Agent();
    void connectAgentToBody();
    // bool doTactic() const {return tactic.doTactic();};

    // Getters
    int getScore();
    b2Body* getBody();


    // Setters
    void setScore(int score);

    private:
        int score = 0;
        int id;
        b2Body* body;
        GameTactic* tactic;

};

#endif // AGENT_H