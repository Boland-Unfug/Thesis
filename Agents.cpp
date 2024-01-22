// #include "Agents.h"
// #include "PhysicsEngine.cpp"

// Agents::Agents() {
//     this->agents = std::vector<Agent*>();
// }

// Agents::~Agents() {
//     for (int i = 0; i < this->agents.size(); i++) {
//         delete this->agents[i];
//     }
// }

// void Agents::newAgent(b2Vec2 position, float radius) {
//     // Make the agent body

//     Agent *agent = new Agent(PhysicsEngine::CreateAgent(position, radius), this->agents.size());
//     // Set the User Data
//     agent->getBody()->SetUserData(agent);

//     this->agents.push_back(agent);


// }

