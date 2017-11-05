#ifndef CROCUS_ANIMATION_H
#define CROCUS_ANIMATION_H

#include "point.h"
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <common.h>
#include <piece.h>

class Animation {
private:
    const Piece *_piece;
    Point _from;
    Point _to;
    Point _currentPoint;
    float _speed;
    bool _infinite;
    bool _finished;
    TimePoint _start;
    std::function<void()> _finishHandler;

public:
    Animation(const Piece *piece, const Point &from, const Point &to,
              float speed, bool infinite = false);
    void update(sf::RenderTarget &renderTarget);
    bool finished() const {
        return _finished;
    }
    void setFinishHandler(std::function<void()> finishHandler) {
        _finishHandler = finishHandler;
    }
};

#endif // CROCUS_ANIMATION_H
