// This will store the game strategies for the agents.

#ifndef GAMETACTIC_H
#define GAMETACTIC_H

class GameTactic
{
    public:
        virtual ~GameTactic() = default;
        virtual unsigned char doTactic() const = 0; // I use unsigned char because it is the same size as bool and mmore flexible
};

#endif // GAMEETACTIC_H