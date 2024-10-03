#ifndef GAMETACTICS_H
#define GAMETACTICS_H

#include "GameTactic.h"
#include <iostream>

class Defect : public GameTactic
{
    public:
        Defect() = default;
        unsigned char doTactic() const override {
            return 0;};
};

class Cooperate : public GameTactic
{
    public:
        Cooperate() = default;
        unsigned char doTactic() const override {
            return 1;};
};

#endif // GAMETACTICS_H