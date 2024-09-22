#ifndef GAMETACTICS_H
#define GAMETACTICS_H

#include "GameTactic.h"
#include <iostream>

class Defect : public GameTactic
{
public:
    Defect() = default;
    bool doTactic(uint16_t opponent) const override { return 1; };    // also sadly have to hand opponent in
    void updateTactic(uint16_t opponent, bool oppchoice) override {}; // I think useless? but necessary?
};

class Cooperate : public GameTactic
{
public:
    Cooperate() = default;
    bool doTactic(uint16_t opponent) const override { return 0; };    // also sadly have to hand opponent in
    void updateTactic(uint16_t opponent, bool oppchoice) override {}; // I think useless? but necessary?
};

class TitForTat : public GameTactic
{
public:
    std::vector<bool> oppchoices;
    TitForTat(int numAgents)
    {
        this->oppchoices.resize(numAgents);
        for (int i = 0; i < numAgents; i++)
        {
            this->oppchoices[i] = 0;
        }
    }
    // I am about to do a coding sin TODO fix this later
    bool doTactic(uint16_t opponent) const override
    {
        return this->oppchoices[opponent];
    };
    void updateTactic(uint16_t opponent, bool oppchoice) override
    {
        this->oppchoices[opponent] = oppchoice;
    };
};

class NaiveTitForTat : public GameTactic
{
public:
    bool oppchoice = 0;
    NaiveTitForTat() = default;
    // I am about to do a coding sin TODO fix this later
    bool doTactic(uint16_t opponent) const override
    {
        return this->oppchoice;
    };
    void updateTactic(uint16_t opponent, bool oppchoice) override
    {
        this->oppchoice = oppchoice;
    };
};

#endif // GAMETACTICS_H