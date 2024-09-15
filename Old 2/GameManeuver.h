// This will store the game strategies for the agents.

#ifndef GAMEMAUEVER_H
#define GAMEMAUEVER_H

#include <box2d/box2d.h>

class GameManeuver
{
    public:
        virtual ~GameManeuver() = default;
        virtual b2Vec2 doManeuver() const = 0; // I use unsigned char because it is the same size as bool and mmore flexible
};

#endif // GAMEMAUEVER_H