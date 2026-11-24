#include <dpp/dpp.h>

#include <vector>
#include <iostream>
#include <stdexcept>
#include <map>
#include <string>

#include "../include/json.hpp"
#include "../include/utils.hpp"
#include "../include/tosiek.hpp"

// main
int main(int argc, char** argv) {

    // initialization
    std::ifstream file("../config.json");
    nlohmann::json data = nlohmann::json::parse(file);
    const std::string BOT_TOKEN = data["token"];
    dpp::cluster bot(BOT_TOKEN, dpp::i_default_intents | dpp::i_message_content);
    
    bool development = true;
    
    bot.on_log(dpp::utility::cout_logger());

    bot.on_message_create([&bot](const dpp::message_create_t& event) {
        logSendMessage(event);
    });

    bot.on_slashcommand([&bot](const dpp::slashcommand_t& event) {
        dpp::command_interaction cmd_data = event.command.get_command_interaction();
        std::string request = event.command.get_command_name();
        try {
            commands::getCommandsMap(bot).at(request).callback(event, cmd_data);
            std::cout << "executed " << request << std::endl;
        } catch (const std::out_of_range& e) {
            tosiek::reject(event);
            std::cout << "tried executing " << request << ", but couldn't find command!";
        }
    });

    bot.on_ready([&bot, &development](const dpp::ready_t& event) {
        if (dpp::run_once<struct register_bot_commands>()) {
            pushAllCommands(bot, development);
        }
    });

    bot.start(dpp::st_wait);
    return 0;
}