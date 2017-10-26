#ifndef CROCUS_CLIENT_BOARD_H
#define CROCUS_CLIENT_BOARD_H

#include "client/common.h"
#include "client_domain.h"
#include "point.h"
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <board.h>
#include <enums.h>
#include <piece.h>
#include <position.h>

class ClientBoard {
private:
    float _leftPadding;
    float _topPadding;
    float _grid;
    const Board &_board;
    sf::RenderTexture _texture;
    Force _viewForce;

public:
    ClientBoard(const Board &board, const Point &topLeft, float grid,
                Force viewForce)
        : _board(board), _leftPadding(topLeft.x()), _topPadding(topLeft.y()),
          _grid(grid), _viewForce(viewForce), _texture() {
        _texture.create(896, 1024);
        _texture.setSmooth(true);
    }

    void draw(sf::RenderWindow &window) {
        draw();
        sf::Sprite sprite(_texture.getTexture());
        sprite.setScale(0.6, 0.6);
        window.draw(sprite);
        _texture.display();
    }

    void draw() {
        _texture.draw(*domain::defaultBoard);
        for (auto piece : _board.all()) {
            draw(piece);
        }
    }

    void draw(const Piece *piece) {
        const Point &point = transform(piece->position(), _viewForce);
        draw(piece, point);
    }

    void draw(const Piece *piece, const Point &point) {
        sf::Sprite *s = domain::redPawn;
        s->setPosition(point.x(), point.y());
        _texture.draw(*s);
    }

    Point topLeft() const {
        return Point(_leftPadding, _topPadding);
    }

    Point transform(const Position &position, Force viewer) const {
        const Position &viewPosition = common::view(position, viewer);
        float offsetX = (9 - viewPosition.x()) * _grid;
        float offsetY = (10 - viewPosition.y()) * _grid;
        return topLeft().move(offsetX, offsetY);
    }
};

#endif // CROCUS_CLIENT_BOARD_H
