#include "client/client_board.h"
#include <SFML/Graphics/Text.hpp>
#include <client/client_game.h>

void ClientBoard::draw(sf::RenderWindow &window, const Point &point,
                       SelectionState *selectionState) {
    draw(selectionState);
    sf::Sprite sprite(_texture.getTexture());
    sprite.setScale(scalar, scalar);
    sprite.setPosition({point.x(), point.y()});
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
    drawText();
}

void ClientBoard::clearAnimations() {
    _animations.remove_if([](auto animation) { return animation->finished(); });
}

void ClientBoard::drawText() {
    if (_text.size() != 0) {
        auto rect = _texture.getViewport(_texture.getDefaultView());
        sf::RectangleShape rectangle;
        rectangle.setSize(
            {static_cast<float>(rect.width), static_cast<float>(rect.height)});
        rectangle.setFillColor(sf::Color{0, 0, 0, 192});
        _texture.draw(rectangle);
        sf::Text text(_text, Sprites::font);
        text.setCharacterSize(64);
        text.setStyle(sf::Text::Bold);
        text.setFillColor(sf::Color::White);
        text.setPosition(50, 50);
        _texture.draw(text);
    }
}
