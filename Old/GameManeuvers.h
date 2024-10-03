#ifndef GAMEMANEUVERS_H
#define GAMEMANEUVERS_H

#include "GameManeuver.h"

class Left : public GameManeuver
{
    public:
        Left();
        ~Left();
        void doManeuver(Agent &agent1) const override;
};

class Right : public GameManeuver
{
    public:
        Right();
        ~Right();
        void doManeuver(Agent &agent1) const override;
};

class Up : public GameManeuver
{
    public:
        Up();
        ~Up();
        void doManeuver(Agent &agent1) const override;
};

class Down : public GameManeuver
{
    public:
        Down();
        ~Down();
        void doManeuver(Agent &agent1) const override;
};

#endif // GAMEMANEUVER_H