#pragma once
#include "Player.h"
#include <vector>
#include <random>
#include <unordered_map>

class PlayerManager {
public:
    PlayerManager();
    void loadPlayers(const std::string& filename);
    const Player& getRandomPlayer();
    const Player& getRandomPlayerByTeam(const std::string& team, int pValue);
    size_t getPlayerCount() const { return players.size(); }
    std::vector<std::string> getTeams() const;

private:
    std::vector<Player> players;
    std::unordered_map<std::string, std::vector<size_t>> teamPlayerIndices;
    std::unordered_map<std::string, std::vector<size_t>> namePlayerIndices;
    std::unordered_map<std::string, std::vector<size_t>> pValueIndices;
    std::mt19937 rng;
};