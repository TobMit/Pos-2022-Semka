#include "Game/Server/ServerGame.h"



int main() {
    ServerGame game;
    if (!game.serverInicialise()) {
        return EXIT_FAILURE;
    }
    game.run();
    return EXIT_SUCCESS;
}
