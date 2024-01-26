#include "Agent.h"
#include <iostream>

Agent::Agent(b2Body* body, int id) : id(id) {
    this->body = body;
    this->id = id;
}

void Agent::connectAgentToBody() {
    this->body->GetUserData().pointer = reinterpret_cast<uintptr_t>(this);
}

Agent::~Agent() {}

int Agent::getScore() {
    return this->score;
}

b2Body* Agent::getBody() {
    return this->body;
}

int Agent::getId() {
    return this->id;
}

void Agent::setScore(int score) {
    this->score = score;
}