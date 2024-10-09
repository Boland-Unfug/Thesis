// This will store the game strategies for the agents.

#ifndef GAMEMAUEVER_H
#define GAMEMAUEVER_H

#include <box2d/box2d.h>

class GameManeuver
{
    public:
        virtual ~GameManeuver() = default;
        // this will now need to take in the collision point and booth agent's choices
        virtual b2Vec2 doManeuver() const = 0; // I use unsigned char because it is the same size as bool and mmore flexible
        virtual void updateManeuver(b2Vec2 contactPoint, b2Vec2 agentPoint) = 0;
};

#endif // GAMEMAUEVER_H