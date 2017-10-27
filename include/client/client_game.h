#ifndef CROCUS_CLIENT_GAME_H
#define CROCUS_CLIENT_GAME_H

#include "client_board.h"
#include <SFML/Window/Event.hpp>
#include <game.h>

class SelectionState {
protected:
    ClientBoard &_clientBoard;
    Force _player;
    SelectionState(ClientBoard &clientBoard, Force player)
        : _clientBoard(clientBoard), _player(player) {}

public:
    virtual SelectionState *awake() {
        return this;
    };
    virtual SelectionState *numb() {
        return this;
    };
    virtual SelectionState *handle(const Point &point) {
        return this;
    };
};

class NumbState : public SelectionState {
public:
    NumbState(ClientBoard &clientBoard, Force player);

    SelectionState *awake() override;
};

class AwakeState : public SelectionState {
public:
    AwakeState(ClientBoard &clientBoard, Force player);

    SelectionState *handle(const Point &point) override;
};

class LoadState : public SelectionState {
public:
    LoadState(ClientBoard &clientBoard, Force player);
    SelectionState *handle(const Point &point) override;
};

class ClientGame {
private:
    Game game;
    ClientBoard clientBoard;

    Force player;
    SelectionState *selectionState;

public:
    ClientGame()
        : game(), clientBoard{game.board(), {42, 52}, 102, Force::RED} {
        player = Force::RED;
        game.board().reset();
        selectionState = new AwakeState(clientBoard, player);
    }

    void handle(sf::Event event) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            const Point &point = Point{static_cast<float>(event.mouseButton.x),
                                       static_cast<float>(event.mouseButton.y)};
            selectionState = selectionState->handle(point);
        }
    }

    void draw(sf::RenderWindow &window) {
        clientBoard.draw(window);
    }
};

#endif // CROCUS_CLIENT_GAME_H
