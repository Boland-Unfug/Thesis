#include "Agent.h"
#include <iostream>

Agent::Agent(b2Body* body, int id) {
    this->body = body;
    this->id = id;
}

void Agent::connectAgentToBody() {
    std::cout << "Connecting agent to body" << std::endl;
    std::cout << "Agent Pointer" << this << std::endl;
    this->body->GetUserData().pointer = reinterpret_cast<uintptr_t>(this);
}

Agent::~Agent() {}

int Agent::getScore() {
    return this->score;
}

b2Body* Agent::getBody() {
    return this->body;
}

void Agent::setScore(int score) {
    this->score = score;
}