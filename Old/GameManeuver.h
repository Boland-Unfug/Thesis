#ifndef GAMEMAUEVER_H
#define GAMEMAUEVER_H

#include "Agent.h"

class GameManeuver
{
    public:
        GameManeuver();
        ~GameManeuver();
        virtual void doManeuver(Agent &agent1) const = 0; // May add a second agent later
};

#endif // GAMEMAUEVER_H