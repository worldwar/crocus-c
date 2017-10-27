#include <client/client_game.h>

NumbState::NumbState(ClientBoard &clientBoard, Force player)
    : SelectionState(clientBoard, player) {}

SelectionState *NumbState::awake() {
    AwakeState *next = new AwakeState(_clientBoard, _player);
    delete this;
    return next;
}

AwakeState::AwakeState(ClientBoard &clientBoard, Force player)
    : SelectionState(clientBoard, player) {}

SelectionState *AwakeState::handle(const Point &point) {
    const Position &position = _clientBoard.transform(point);
    if (position.legal()) {
        Piece *piece = _clientBoard.piece(position);
        if (piece != nullptr && _player == piece->force()) {
            _clientBoard.select(piece);
            LoadState *next = new LoadState(_clientBoard, _player);
            delete this;
            return next;
        }
    }
    return SelectionState::handle(point);
}

LoadState::LoadState(ClientBoard &clientBoard, Force player)
    : SelectionState(clientBoard, player) {}

SelectionState *LoadState::handle(const Point &point) {
    const Position &position = _clientBoard.transform(point);
    if (position.legal()) {
        Piece *piece = _clientBoard.piece(position);

        if (piece == _clientBoard.selectedPiece()) {
            _clientBoard.unselect();
            auto *next = new AwakeState(_clientBoard, _player);
            delete this;
            return next;
        } else {
            if (piece != nullptr && piece->force() == _player) {
                _clientBoard.select(piece);
                return this;
            }
        }

        if (_clientBoard.moveTo(point)) {
            NumbState *next = new NumbState(_clientBoard, _player);
            delete this;
            return next;
        }
    }
    return SelectionState::handle(point);
}
