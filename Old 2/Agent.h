#ifndef AGENT_H
#define AGENT_H

#include <Box2D/Box2D.h>
#include "GameTactics.h"
#include "GameManeuvers.h"

class Agent {
public:
    Agent(b2Body* body, int id);
    ~Agent();

    void connectAgentToBody();

    unsigned char doTactic() const {
        return tactic->doTactic();};

    b2Vec2 doManeuver() const {
        return maneuver->doManeuver();};

    // Getters
    int getScore();
    int getId();
    b2Body* getBody();
    Agent getAgent() {return *this;};
    GameTactic* getTactic() {return this->tactic;};
    GameManeuver* getManeuver() {return this->maneuver;};


    // Setters
    void setScore(int score);
    void setTactic(GameTactic* tactic) {this->tactic = tactic;};
    void setManeuver(GameManeuver* maneuver) {this->maneuver = maneuver;};

    private:
        int score = 0;
        int id = 0;
        b2Body* body;
        GameTactic* tactic;
        GameManeuver* maneuver;
};

#endif // AGENT_H