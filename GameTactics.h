#ifndef GAMETACTICS_H
#define GAMETACTICS_H

#include "GameTactic.h"
#include <iostream>

class Defect : public GameTactic
{
    public:
        Defect() = default;
        bool doTactic(uint16_t opponent)const override {return 1;}; // also sadly have to hand opponent in
        void updateTactic(uint16_t opponent, bool oppchoice) override {}; // I think useless? but necessary?
};

class Cooperate : public GameTactic
{
    public:
        Cooperate() = default;
        bool doTactic(uint16_t opponent)const override {return 1;}; // also sadly have to hand opponent in
        void updateTactic(uint16_t opponent, bool oppchoice) override {}; // I think useless? but necessary?
};

class TitForTat : public GameTactic
{
    public:
        TitForTat(int numAgents) {
            this->numAgents = numAgents;
            this->grudges[numAgents] = {0}; // set cooperate as default
        };
        // I am about to do a coding sin TODO fix this later
        bool doTactic(uint16_t opponent) const override {
            return this->grudges[opponent];};

        void updateTactic(uint16_t opponent, bool oppchoice) override {
            this->grudges[opponent] = oppchoice;
        };
        
        
    private:
        int numAgents;
        bool grudges[];
};

#endif // GAMETACTICS_H