#ifndef CROCUS_CLIENT_GAME_H
#define CROCUS_CLIENT_GAME_H

#include "client/animation.h"
#include "client/client_board.h"
#include "client/control_board.h"
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
    ControlBoard _controlBoard;
    Force _player;
    SelectionState *selectionState;
    GameContext *context;
    Sender *sender;
    std::mutex _mutex;
    const Point boardPosition;

public:
    ClientGame();
    void init();

    void handle(sf::Event event) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            const Point &point = Point{static_cast<float>(event.mouseButton.x),
                                       static_cast<float>(event.mouseButton.y)};
            const Point &p = point.move(-boardPosition.x(), -boardPosition.y());
            selectionState = selectionState->handleClick(context, p);
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

    void ready();

    void unready();

    GameState state() const {
        return game.state();
    }

    void apply(const Action &action) {
        const Piece &piece = action.piece();
        game.play(&piece, action.target());
    }
};

#endif // CROCUS_CLIENT_GAME_H
