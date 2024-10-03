#ifndef GAMEMANEUVERS_H
#define GAMEMANEUVERS_H

#include <iostream>
#include <random>

#include "GameManeuver.h"


class Up : public GameManeuver
{
    public:
        Up() = default;
        b2Vec2 doManeuver() const override {
            return b2Vec2(0.0f, -0.01f);};
};

class Down : public GameManeuver
{
    public:
        Down() = default;
        b2Vec2 doManeuver() const override {
            return b2Vec2(0.0f, 0.01f);};
};

class Left : public GameManeuver
{
    public:
        Left() = default;
        b2Vec2 doManeuver() const override {
            return b2Vec2(-0.01f, 0.0f);};
};

class Right : public GameManeuver
{
    public:
        Right() = default;
        b2Vec2 doManeuver() const override {
            return b2Vec2(0.01f, 0.0f);};
};

class Random : public GameManeuver
{
    public:
        Random() = default;
        b2Vec2 doManeuver() const override {
            return b2Vec2((rand() % 3) - 1, (rand() % 3) - 1);};
};

class Still : public GameManeuver
{
    public:
        Still() = default;
        b2Vec2 doManeuver() const override {
            return b2Vec2(0.0f, 0.0f);};
};

#endif // GAMEMANEUVERS_H