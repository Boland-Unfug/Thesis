#ifndef GAMEMANEUVERS_H
#define GAMEMANEUVERS_H

#include <iostream>
#include <random>

#include "GameManeuver.h"


class Up : public GameManeuver // represented by 'u'
{ 
    public:
        Up() = default;
        b2Vec2 doManeuver() const override {
            return b2Vec2(0.0f, -0.01f);};
};

class Down : public GameManeuver // represented by 'd'
{
    public:
        Down() = default;
        b2Vec2 doManeuver() const override {
            return b2Vec2(0.0f, 0.01f);};
};

class Left : public GameManeuver // represented by 'l'
{
    public:
        Left() = default;
        b2Vec2 doManeuver() const override {
            return b2Vec2(-0.01f, 0.0f);};
};

class Right : public GameManeuver // represented by 'r'
{
    public:
        Right() = default;
        b2Vec2 doManeuver() const override {
            return b2Vec2(0.01f, 0.0f);};
};

class Random : public GameManeuver // represented by 'R'
{
    public:
        Random() = default;
        b2Vec2 doManeuver() const override {
            return b2Vec2((rand() % 3) - 1, (rand() % 3) - 1);};
};

class Still : public GameManeuver // represented by 's'
{
    public:
        Still() = default;
        b2Vec2 doManeuver() const override {
            return b2Vec2(0.0f, 0.0f);};
};

class Chase : public GameManeuver // represented by 'c'
{
    public:
        b2Vec2 push = b2Vec2(0.0f, 0.0f);
        Chase() = default;
        b2Vec2 doManeuver() const override {
            return this->push;};
        void updateManeuver(b2Vec2 contactPoint, b2Vec2 agentPoint) override {
            this->push = contactPoint - agentPoint;
        };
};

class Flee : public GameManeuver // represented by 'f'
{
    public:
        b2Vec2 push = b2Vec2(0.0f, 0.0f);
        Flee() = default;
        b2Vec2 doManeuver() const override {
            return this->push;};
        void updateManeuver(b2Vec2 contactPoint, b2Vec2 agentPoint) override {
            this->push = agentPoint - contactPoint;
        };
};

class WinChase : public GameManeuver // represented by 'W'
{
    public:
        b2Vec2 push = b2Vec2(0.0f, 0.0f);
        WinChase() = default;
        b2Vec2 doManeuver() const override {
            return this->push;};
        void updateManeuver(b2Vec2 contactPoint, b2Vec2 agentPoint) override {
            this->push = contactPoint - agentPoint;
        };
};

class LossFlee : public GameManeuver // represented by 'L'
{
    public:
        b2Vec2 push = b2Vec2(0.0f, 0.0f);
        LossFlee() = default;
        b2Vec2 doManeuver() const override {
            return this->push;};
        void updateManeuver(b2Vec2 contactPoint, b2Vec2 agentPoint) override {
            this->push = agentPoint - contactPoint;
        };
};
#endif // GAMEMANEUVERS_H