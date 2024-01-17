// This will store the game strategies for the agents.

#ifndef GAMETACTIC_H
#define GAMETACTIC_H

class GameTactic
{
    public:
        virtual ~GameTactic();
        virtual bool doTactic() const = 0;
};

#endif // GAMEETACTIC_H