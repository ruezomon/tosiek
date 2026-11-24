#include <fstream>
#include <cmath>
#include <vector>
#include <map>
#include <string>
#include <stdexcept>
#include <functional>

#include "json.hpp"
#include "utils.hpp"
#include "tosiek.hpp"

std::string lowerCase(std::string before) {
    std::string after = "";
    for (char i : before) {
        after += std::tolower(i);
    }
    return after;
}

int isSubstring(std::string s1, std::string s2) {
    int M = s1.length();
    int N = s2.length();

    for (int i = 0; i <= N - M; i++) {
        int j;
        for (j = 0; j < M; j++)
            if (s2[i + j] != s1[j])
                break;

        if (j == M)
            // right here, i also contains the index of the substring
            // return i;
            return true;
    }
    return false;
}

void pushAllCommands(dpp::cluster& bot, bool development) {
    std::vector<dpp::slashcommand> stack;
    auto commandsMap = commands::getCommandsMap(bot);

    for (uint8_t i = 0; i < commands::COMMAND_NAMES.size(); i++)
        stack.push_back(commandsMap[commands::COMMAND_NAMES[i]].command);

    std::cout << "Following commands should now be in available: " << std::endl;
    for (int i = 0; i < stack.size(); i++) {
        std::cout << stack[i].name << std::endl;
    }
    std::cout << std::endl;

    if (!development)
        bot.global_bulk_command_create(stack);
    else {
        std::cout << "development variable true; will prioritize testing guild" << std::endl;
        bot.guild_bulk_command_create(stack, 1574891258600755280);
    }
}

uint32_t timeToSeconds(std::string time) {
    /*
    possible units are:
    s ... seconds
    m ... minutes
    h ... hours
    d ... days

    must use full integers
    */

    std::function<uint32_t(uint32_t)> converter;
    switch (time[time.length() - 1]) {
        case 's':
            converter = [](uint32_t s) { return s; };
            break;
        case 'm':
            converter = [](uint32_t s) { return s * 60; };
            break;
        case 'h':
            converter = [](uint32_t s) { return s * 3600; };
            break;
        case 'd':
            converter = [](uint32_t s) { return s * 86400; };
            break;
        default:
            return 0;
    }
    time.erase(time.length() - 1);

    char* err;
    strtol(time.c_str(), &err, 10);
    if (err) return 0;

    return converter([time]() { 
        uint32_t n = 0; 
        for (uint8_t i = time.length() - 1; i >= 0; i--)
            n += (time[i] - '0') * pow(10, time.length() - i - 1);
        return n;
    }());
}

void logSendMessage(const dpp::message_create_t& event) {
    std::cout 
        << "message sent by: " 
        << event.msg.author.id.str() 
        << " ("
        << event.msg.author.get_mention()
        << " ); in server: "
        << event.msg.guild_id.str()
        << std::endl;
}

std::map<std::string, bool> getProgramParams(int argc, char** argv) {
    std::map<std::string, bool> params = {
        {"develop", false},
    };
    for (uint8_t i = 1; i < argc; i++) {
        auto it = params.find(argv[i]);
        if (it == params.end())
            throw std::invalid_argument("bad parameter");
        it->second = true;
    }
    return params;
}
