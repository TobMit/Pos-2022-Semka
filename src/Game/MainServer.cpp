#include "Server/ServerGame.h"



int main() {
    ServerGame game;
    if (!game.serverInitialize()) {
        return EXIT_FAILURE;
    }
    game.run();
    return EXIT_SUCCESS;
}
