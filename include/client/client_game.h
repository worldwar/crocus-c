#ifndef CROCUS_CLIENT_GAME_H
#define CROCUS_CLIENT_GAME_H

#include "client/animation.h"
#include "client/client_board.h"
#include "client/selection_state.h"
#include <SFML/Window/Event.hpp>
#include <game.h>

class GameContext;
class ClientGame {
private:
    Game game;
    ClientBoard clientBoard;
    Force _player;
    SelectionState *selectionState;
    GameContext *context;

public:
    ClientGame();

    void handle(sf::Event event) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            const Point &point = Point{static_cast<float>(event.mouseButton.x),
                                       static_cast<float>(event.mouseButton.y)};
            selectionState = selectionState->handleClick(context, point);
        }
    }

    void handleFinish() {
        selectionState = selectionState->finish(context);
    }

    void draw(sf::RenderWindow &window);

    void add(Animation *animation) {
        clientBoard.add(animation);
    }

    void printState();

    Force player() const {
        return _player;
    }
};

#endif // CROCUS_CLIENT_GAME_H
