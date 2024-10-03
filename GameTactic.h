// This will store the game strategies for the agents.

#ifndef GAMETACTIC_H
#define GAMETACTIC_H

class GameTactic
{
    public:
        virtual ~GameTactic() = default;
        virtual void updateTactic(uint16_t opponent, bool oppchoice) = 0;
        virtual bool doTactic(uint16_t opponent) const = 0;
};

#endif // GAMEETACTIC_H