#ifndef CROCUS_CLIENT_GAME_H
#define CROCUS_CLIENT_GAME_H

#include "client/animation.h"
#include "client/client_board.h"
#include "client/selection_state.h"
#include "network/sender.h"
#include <SFML/Window/Event.hpp>
#include <game.h>
#include <iostream>
#include <mutex>

class GameContext;
class ClientGame {
private:
    Game game;
    ClientBoard clientBoard;
    Force _player;
    SelectionState *selectionState;
    GameContext *context;
    Sender *sender;
    std::mutex _mutex;

public:
    ClientGame();
    void init();

    void handle(sf::Event event) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            const Point &point = Point{static_cast<float>(event.mouseButton.x),
                                       static_cast<float>(event.mouseButton.y)};
            selectionState = selectionState->handleClick(context, point);
        }
    }

    void handle(const Packet *packet);

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

    void send(const Action &action);

    void startReceive();

    std::mutex &mutex() {
        return _mutex;
    }

    void begin(Force force);

    void end(GameResult result, GameEndReason reason);

    void reset();

    void showText(const std::wstring &text);
};

#endif // CROCUS_CLIENT_GAME_H
