#ifndef HISTORY_H
#define HISTORY_H

#include <iostream>
#include <unordered_map>

class History {
public:
    History() {}
    ~History() {}

    // Hash function
    size_t createHash(int round, int agentId1, int agentId2) const {
        return ((size_t)round << 32) | ((size_t)agentId1 << 16) | (size_t)agentId2;
    }

    // Function to add a new entry using hash
    void addEntry(int round, int agentId1, int agentId2, int value) {
        size_t hash = createHash(round, agentId1, agentId2);
        history[hash] = value;
    }

    // Function to get entries using hash
    int getEntry(int round, int agentId1, int agentId2) const {
        size_t hash = createHash(round, agentId1, agentId2);
        auto it = history.find(hash);
        if (it != history.end()) {
            return it->second;
        } else {
            throw std::runtime_error("Entry not found");
        }
    }

    int getEntry(size_t hash) const {
        auto it = history.find(hash);

private:
    std::unordered_map<size_t, int> history;
};
};
#endif // HISTORY_H