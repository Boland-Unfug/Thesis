#include "Agent.h"
#include <iostream>

Agent::Agent(b2Body* body, int id) : id(id) {
    this->body = body;
    this->id = id;
}

void Agent::connectAgentToBody() {
    std::cout<< "The pointer: " << this << std::endl;
    std::cout<< "The body pointer: " << this->body << std::endl;
    std::cout<< "The ID" << this->id << std::endl;
    uintptr_t pointer = reinterpret_cast<uintptr_t>(this);
    std::cout<< "The reinterpreted pointer: " << pointer << std::endl;

    this->body->GetUserData().pointer = reinterpret_cast<uintptr_t>(this);

    std::cout<< "The reinterpreted pointer: " << this->body->GetUserData().pointer << std::endl;
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