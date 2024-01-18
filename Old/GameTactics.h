#ifndef GAMETACTICS_H
#define GAMETACTICS_H

#include "GameTactic.h"

class Betray : public GameTactic
{
    public:
        bool doTactic() const override {return 0;};
};

class Cooperate : public GameTactic
{
    public:
        bool doTactic() const override {return 1;};
};

#endif // GAMETACTICS_H