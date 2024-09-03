#ifndef GAMEMANEUVERS_H
#define GAMEMANEUVERS_H

#include "GameManeuver.h"
#include <iostream>

class Up : public GameManeuver
{
    public:
        Up() = default;
        b2Vec2 doManeuver() const override {
            return b2Vec2(0.0f, -1.0f);};
};

class Down : public GameManeuver
{
    public:
        Down() = default;
        b2Vec2 doManeuver() const override {
            return b2Vec2(0.0f, 1.0f);};
};

class Left : public GameManeuver
{
    public:
        Left() = default;
        b2Vec2 doManeuver() const override {
            return b2Vec2(-1.0f, 0.0f);};
};

class Right : public GameManeuver
{
    public:
        Right() = default;
        b2Vec2 doManeuver() const override {
            return b2Vec2(1.0f, 0.0f);};
};

#endif // GAMEMANEUVERS_H