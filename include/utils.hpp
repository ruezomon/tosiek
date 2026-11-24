#pragma once

#include <dpp/dpp.h>
#include <vector>
#include <map>
#include <chrono>

struct Command {
    std::string name;
    dpp::slashcommand command;
    std::function<void(const dpp::slashcommand_t& event, dpp::command_interaction cmd_data)> callback;
};

// --- essentials ---
void pushAllCommands(dpp::cluster& bot, bool development = false);
void timeout(const dpp::slashcommand_t& event, dpp::snowflake target_user_id, int duration_seconds, bool log = true, bool follow_up = false);

// --- utils ---
bool isNumber(std::string strNumber);
std::string diceRoll(int low, int up);
std::string lowerCase(std::string before);
int isSubstring(std::string s1, std::string s2);
uint32_t timeToSeconds(std::string time);
void logSendMessage(const dpp::message_create_t& event);
std::map<std::string, bool> getProgramParams(int argc, char** argv);

// --- blacklist ---
std::vector<std::string> getBadWords();
bool isBadWord(const dpp::message_create_t& event, std::vector<std::string>& badWords);