#ifndef AGENTMANAGER_H
#define AGENTMANAGER_H

#include <vector>
#include <Box2D/Box2D.h>
#include "Agent.h"
#include "GameTactics.h"

class AgentManager {
public:
    AgentManager();
    ~AgentManager();

    void addAgent(b2Body* body, int id);
    void addAgent(b2Body* body, int id, GameTactic* tactic);
    void removeAgent(int id);
    void removeAgent(b2Body* body);
    void removeAgent(Agent agent);
    void removeAgent(Agent* agent);
    Agent* getAgent(int id);
    Agent* getAgent(b2Body* body);

    std::vector<Agent*> getAgents();
    
    void setAgentTactic(int id, GameTactic* tactic);
    void setAgentTactic(b2Body* body, GameTactic* tactic);

    void connectAgentsToBodies();

private:
    std::vector<Agent*> agents;
};

#endif // AGENTMANAGER_H