#ifndef GAMEMANEUVERS_H
#define GAMEMANEUVERS_H

#include <iostream>
#include <random>

#include "GameManeuver.h"

class Up : public GameManeuver
{
public:
    Up() = default;
    b2Vec2 doManeuver() const override
    {
        return b2Vec2(0.0f, -0.01f);
    };
    void updateManeuver(b2Vec2 contactPoint, b2Vec2 agentPoint) override
    {
        // do nothing
    };
};

class Down : public GameManeuver
{
public:
    Down() = default;
    b2Vec2 doManeuver() const override
    {
        return b2Vec2(0.0f, 0.01f);
    };
    void updateManeuver(b2Vec2 contactPoint, b2Vec2 agentPoint) override
    {
        // do nothing
    };
};

class Left : public GameManeuver
{
public:
    Left() = default;
    b2Vec2 doManeuver() const override
    {
        return b2Vec2(-0.01f, 0.0f);
    };
    void updateManeuver(b2Vec2 contactPoint, b2Vec2 agentPoint) override
    {
        // do nothing
    };
};

class Right : public GameManeuver
{
public:
    Right() = default;
    b2Vec2 doManeuver() const override
    {
        return b2Vec2(0.01f, 0.0f);
    };
    void updateManeuver(b2Vec2 contactPoint, b2Vec2 agentPoint) override
    {
        // do nothing
    };
};

class Random : public GameManeuver
{
public:
    Random() = default;
    b2Vec2 doManeuver() const override
    {
        return b2Vec2((rand() % 3) - 1, (rand() % 3) - 1);
    };
    void updateManeuver(b2Vec2 contactPoint, b2Vec2 agentPoint) override
    {
        // do nothing
    };
};

class Still : public GameManeuver
{
public:
    Still() = default;
    b2Vec2 doManeuver() const override
    {
        return b2Vec2(0.0f, 0.0f);
    };
    void updateManeuver(b2Vec2 contactPoint, b2Vec2 agentPoint) override
    {
        // do nothing
    };
};

class Chase : public GameManeuver
{
public:
    b2Vec2 push = b2Vec2(0.0f, 0.0f);
    Chase() = default;
    b2Vec2 doManeuver() const override
    {
        return this->push;
    };
    void updateManeuver(b2Vec2 contactPoint, b2Vec2 agentPoint) override
    {
        this->push = contactPoint - agentPoint;
    };
};

class Flee : public GameManeuver
{
public:
    b2Vec2 push = b2Vec2(0.0f, 0.0f);
    Flee() = default;
    b2Vec2 doManeuver() const override
    {
        return this->push;
    };
    void updateManeuver(b2Vec2 contactPoint, b2Vec2 agentPoint) override
    {
        this->push = agentPoint - contactPoint;
    };
};

class WinChase : public GameManeuver
{
public:
    b2Vec2 push = b2Vec2(0.0f, 0.0f);
    WinChase() = default;
    b2Vec2 doManeuver() const override
    {
        return this->push;
    };
    void updateManeuver(b2Vec2 contactPoint, b2Vec2 agentPoint) override
    {
        this->push = contactPoint - agentPoint;
    };
};

class LossFlee : public GameManeuver
{
public:
    b2Vec2 push = b2Vec2(0.0f, 0.0f);
    LossFlee() = default;
    b2Vec2 doManeuver() const override
    {
        return this->push;
    };
    void updateManeuver(b2Vec2 contactPoint, b2Vec2 agentPoint) override
    {
        this->push = agentPoint - contactPoint;
    };
};
#endif // GAMEMANEUVERS_H