#ifndef CROCUS_CONTROL_BOARD_H
#define CROCUS_CONTROL_BOARD_H

#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <client/gui/imgui/imgui-SFML.h>

class ClientGame;
class ControlBoard {
private:
    sf::RenderTexture _texture;
    sf::Clock _deltaClock;
    ClientGame *_game;
    bool _ready = false;

public:
    ControlBoard(ClientGame *game) : _game(game) {
        _texture.create(200, 640);
    }

    void draw(sf::RenderWindow &window);

    void setReady(bool ready) {
        this->_ready = ready;
    }

    bool ready() const {
        return _ready;
    }

    void reset() {
        setReady(false);
    }
};
#endif // CROCUS_CONTROL_BOARD_H
