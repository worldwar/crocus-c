#ifndef CROCUS_CLIENT_BOARD_H
#define CROCUS_CLIENT_BOARD_H

#include "client/animation.h"
#include "client/client_common.h"
#include "client/selection_state.h"
#include "point.h"
#include "sprites.h"
#include <SFML/Graphics/RectangleShape.hpp>
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
    Board &_board;
    sf::RenderTexture _texture;
    Force _viewForce;
    Piece *_selectedPiece;
    Piece *_movingPiece;
    float scalar = 0.6;
    std::list<Animation *> _animations;

public:
    ClientBoard(Board &board, const Point &topLeft, float grid, Force viewForce)
        : _board(board), _leftPadding(topLeft.x()), _topPadding(topLeft.y()),
          _grid(grid), _viewForce(viewForce), _texture(),
          _selectedPiece(nullptr), _movingPiece(nullptr) {
        _texture.create(896, 1024);
        _texture.setSmooth(true);
    }
    void draw(sf::RenderWindow &window, SelectionState *selectionState);
    void draw(SelectionState *selectionState);

    void draw(const Piece *piece) {
        const Point &point = transform(piece->position(), _viewForce);
        draw(piece, point);
    }

    void draw(const Piece *piece, const Point &point) {
        sf::Sprite *s = Sprites::sprite(piece);
        s->setPosition(point.x(), point.y());
        _texture.draw(*s);
        if (piece == _selectedPiece || piece == _movingPiece) {
            const sf::IntRect &rect = s->getTextureRect();
            sf::RectangleShape rectangle;
            rectangle.setSize({static_cast<float>(rect.width),
                               static_cast<float>(rect.height)});
            rectangle.setOrigin(rect.width / 2, rect.height / 2);
            rectangle.setOutlineColor(sf::Color::Red);
            rectangle.setFillColor(sf::Color::Transparent);
            rectangle.setOutlineThickness(5);
            rectangle.setScale(0.3, 0.3);
            rectangle.setPosition(point.x(), point.y());
            _texture.draw(rectangle);
        }
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

    Position transform(const Point &point) const {
        int x = 9 - (point.x() - topLeft().x()) / scalar / _grid;
        int y = 10 - (point.y() - topLeft().y()) / scalar / _grid;
        return common::view({x, y}, _viewForce);
    }

    Piece *piece(const Position &position) const {
        return _board.piece(position);
    }

    void select(Piece *piece) {
        _selectedPiece = piece;
    }

    void unselect() {
        _selectedPiece = nullptr;
    }

    void moveTo(const Point &point) const {
        const Position &position = transform(point);

        const Action &action = _board.makeAction(_selectedPiece, position);
        if (legal(point)) {

            _board.apply(action);
        }
    }

    bool legal(const Point &point) const {
        const Position &position = transform(point);

        const Action &action = _board.makeAction(_selectedPiece, position);
        return _board.legal(action);
    }

    const Piece *selectedPiece() const {
        return _selectedPiece;
    }

    const Piece *movingPiece() const {
        return _movingPiece;
    }

    void moving(Piece *piece) {
        _movingPiece = piece;
    }

    void stopMoving() {
        _movingPiece = nullptr;
    }

    void add(Animation *animation) {
        _animations.push_back(animation);
    }

    void clearAnimations();

    Board &board() {
        return _board;
    }

    void setView(Force force) {
        _viewForce = force;
    }
};

#endif // CROCUS_CLIENT_BOARD_H
