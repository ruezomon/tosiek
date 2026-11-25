#include <thread>
#include <ctime>
#include <chrono>

#include <dpp/dpp.h>
#include "tosiek.hpp"
#include "utils.hpp"

// reject is special and not a slashcommand!
void tosiek::reject(const dpp::slashcommand_t& event) {
    event.reply("Sorry! Couldn't find that command! This is either an issue on our side, or by Discord :)");
}

void tosiek::ping(const dpp::slashcommand_t& event, dpp::command_interaction cmd_data) {
    event.reply("Bot is active and running!");
}

void tosiek::ip(const dpp::slashcommand_t& event, dpp::command_interaction cmd_data) {
    event.reply(getPublicIP());
}

std::map<std::string, Command> commands::getCommandsMap(dpp::cluster& bot) {
    std::map<std::string, Command> commands = {
        {
            "ping", Command{
                .name = "ping", 
                .command = dpp::slashcommand("ping", "Test connection", bot.me.id), 
                .callback = tosiek::ping
            }
        },
        {
            "ip", Command{
                .name = "ip",
                .command = dpp::slashcommand("ip", "Get the IP of the host-server for this bot", bot.me.id),
                .callback = tosiek::ip
            }
        },
    };
    return commands;
}