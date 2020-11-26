#include <iostream>
#include <cxxopts.hpp>
#include <yaml-cpp/yaml.h>
#ifdef ENABLE_LOG
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#endif

#include "network/server.h"
#include "network/client.h"
#include "game/game_board.h"
#include "game/player.h"
#include "common/util.h"
#include "common/config.h"

using namespace UNO;

int main(int argc, char **argv)
{
#ifdef ENABLE_LOG
    spdlog::set_level(spdlog::level::info);
    spdlog::set_default_logger(spdlog::basic_logger_mt("UNO", "logs/log.txt"));
    spdlog::default_logger()->flush_on(spdlog::level::info);
    spdlog::info("hello, spdlog");
#endif

    auto configInfo = Common::Config(argc, const_cast<const char **>(argv)).Parse();

    if (configInfo->mIsServer) {
        auto serverSp = Game::GameBoard::CreateServer(configInfo->mPort);
        Game::GameBoard gameBoard(serverSp);
    }
    else {
        auto clientUp = Game::Player::CreateClient(configInfo->mHost, configInfo->mPort);
        Game::Player player(configInfo->mUsername, clientUp);
    }

    return 0;
}