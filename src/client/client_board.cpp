#include "client/client_board.h"
#include <client/client_game.h>

void ClientBoard::draw(sf::RenderWindow &window,
                       SelectionState *selectionState) {
    draw(selectionState);
    sf::Sprite sprite(_texture.getTexture());
    sprite.setScale(scalar, scalar);
    window.draw(sprite);
    _texture.display();
}

void ClientBoard::draw(SelectionState *selectionState) {
    _texture.draw(*Sprites::defaultBoard);
    for (auto piece : _board.all()) {
        if (selectionState == SelectionStates::shotState() ||
            selectionState == SelectionStates::opposedForceShotState()) {
            if (piece != selectedPiece() && piece != movingPiece()) {
                draw(piece);
            }
        } else {
            draw(piece);
        }
    }
    for (auto animation : _animations) {
        animation->update(_texture);
    }
    clearAnimations();
}

void ClientBoard::clearAnimations() {
    _animations.remove_if([](auto animation) { return animation->finished(); });
}