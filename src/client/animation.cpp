#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <client/animation.h>
#include <client/sprites.h>
#include <cmath>

Animation::Animation(const Piece *piece, const Point &from, const Point &to,
                     float speed, bool infinite)
    : _from(from), _to(to), _currentPoint(from) {
    this->_piece = piece;
    this->_infinite = infinite;
    _start = Clock::now();
    _speed = speed;
}

void Animation::update(sf::RenderTarget &renderTarget) {
    float offset = _speed;
    _currentPoint = _currentPoint.move(offset * (_to.x() - _from.x()),
                                       offset * (_to.y() - _from.y()));

    if (std::abs(_currentPoint.x() - _to.x()) +
            std::abs(_currentPoint.y() - _to.y()) <
        1.0f) {
        _finished = true;
    }

    if (!_finished) {
        sf::Sprite *sprite = Sprites::sprite(_piece);
        sprite->setPosition({_currentPoint.x(), _currentPoint.y()});
        renderTarget.draw(*sprite);
    } else {
        _finishHandler();
    }
}
