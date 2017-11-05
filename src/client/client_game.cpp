#include "client/game_context.h"
#include <iostream>

ClientGame::ClientGame()
    : game(), clientBoard{game.board(), {42, 52}, 102, Force::RED} {
    _player = Force::RED;
    game.board().reset();
    selectionState = SelectionStates::state(2);
    context = new GameContext(this, clientBoard);
}

void ClientGame::draw(sf::RenderWindow &window) {
    clientBoard.draw(window, selectionState);
}

void ClientGame::printState() {
    std::cout << "selectionState: " << selectionState->type() << std::endl;
}
