#pragma once

#include <dpp/dpp.h>
#include "utils.hpp"

namespace tosiek {
    void ping(const dpp::slashcommand_t& event, dpp::command_interaction cmd_data);
    void ip(const dpp::slashcommand_t& event, dpp::command_interaction cmd_data);
    void reject(const dpp::slashcommand_t& event);
}

namespace commands {
    const std::vector<std::string> COMMAND_NAMES = {
        "ping", "ip"
    };
    std::map<std::string, Command> getCommandsMap(dpp::cluster& bot);
}

namespace passive {

}