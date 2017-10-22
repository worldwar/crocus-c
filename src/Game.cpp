#include <game.h>

void Game::start() {
    if (_state == GameState::NOT_STARTED) {
        _board.reset();
        _state = GameState::STARTED;
        _turn = Force::RED;
        _startDate = Clock::now();
        _turnStartDate = _startDate;
    }
}

bool Game::play(const Piece *piece, const Position &position) {
    if (_state != GameState::STARTED)
        return false;
    if (_turn != piece->force())
        return false;
    if (!position.legal())
        return false;

    Action action = _board.makeAction(piece, position);
    if (_board.legal(action)) {
        _board.apply(action);
        next();
        return true;
    } else {
        return false;
    }
}

bool Game::play(const Position &from, const Position &to) {
    Piece *piece = _board.piece(from);
    if (piece != nullptr) {
        return play(piece, to);
    }
    return false;
}

void Game::move(const Position &from, const Position &to) {
    Piece *piece = _board.piece(from);
    if (piece != nullptr) {
        _board.move(piece, to);
    }
}
