//
// Created by Matúš Mištrik on 30/12/2022.
//

#include "ClientGame.h"

void ClientGame::run() {
    while (game.isRunning()) {
        auto nieco = game.processEvents();
    }
}

void ClientGame::update(ServerData data) {
    game.update(data);
    game.render();
}
