#ifndef CROCUS_GAMECONTEXT_H
#define CROCUS_GAMECONTEXT_H

#include "client/client_board.h"
#include "client/client_game.h"

class ClientGame;
class ClientBoard;
class GameContext {
private:
    ClientGame *_clientGame;
    ClientBoard &_clientBoard;

public:
    GameContext(ClientGame *clientGame, ClientBoard &clientBoard)
        : _clientGame(clientGame), _clientBoard(clientBoard) {}

    ClientGame *clientGame() const {
        return _clientGame;
    }

    ClientBoard &clientBoard() {
        return _clientBoard;
    }
};

#endif // CROCUS_GAMECONTEXT_H
