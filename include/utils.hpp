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

// --- utils ---
std::string lowerCase(std::string before);
int isSubstring(std::string s1, std::string s2);
uint32_t timeToSeconds(std::string time);
void logSendMessage(const dpp::message_create_t& event);
std::map<std::string, bool> getProgramParams(int argc, char** argv);
std::string getPublicIP();

// --- blacklist ---
std::vector<std::string> getBadWords();