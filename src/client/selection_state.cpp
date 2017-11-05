#include "client/selection_state.h"
#include "client/client_board.h"
#include "client/game_context.h"
NumbState::NumbState(int type) : SelectionState(type) {}

SelectionState *NumbState::awake(GameContext *context) {
    return SelectionStates::awakeState();
}

AwakeState::AwakeState(int type) : SelectionState(type) {}

SelectionState *AwakeState::handleClick(GameContext *context,
                                        const Point &point) {
    ClientBoard &board = context->clientBoard();
    const Position &position = board.transform(point);
    if (position.legal()) {
        Piece *piece = board.piece(position);
        if (piece != nullptr &&
            context->clientGame()->player() == piece->force()) {
            board.select(piece);
            return SelectionStates::loadState();
        }
    }
    return this;
}

LoadState::LoadState(int type) : SelectionState(type) {}

SelectionState *LoadState::handleClick(GameContext *context,
                                       const Point &point) {
    ClientBoard &board = context->clientBoard();
    Force player = context->clientGame()->player();
    const Position &position = board.transform(point);
    if (position.legal()) {
        Piece *piece = board.piece(position);
        if (piece == board.selectedPiece()) {
            board.unselect();
            return SelectionStates::awakeState();
        } else {
            if (piece != nullptr && piece->force() == player) {
                board.select(piece);
                return this;
            }
        }
        const Position &from = board.selectedPiece()->position();
        const Point &fromPoint = board.transform(from, player);
        const Point &toPoint = board.transform(position, player);
        Board &coreBoard = board.board();
        const Action &action =
            coreBoard.makeAction(board.selectedPiece(), position);
        if (board.legal(point)) {
            Animation *animation =
                new Animation{board.selectedPiece(), fromPoint, toPoint, 0.02};
            std::function<void()> handler = [context, &coreBoard, action]() {
                context->clientGame()->handleFinish();
                coreBoard.apply(action);
            };
            animation->setFinishHandler(handler);
            context->clientGame()->add(animation);
            return SelectionStates::shotState();
        }
    }
    return this;
}

ShotState::ShotState(int type) : SelectionState(type) {}

SelectionState *ShotState::finish(GameContext *context) {
    return SelectionStates::awakeState();
}

OpposedForceShotState::OpposedForceShotState(int type) : SelectionState(type) {}

SelectionState *OpposedForceShotState::finish(GameContext *context) {
    return SelectionStates::awakeState();
}

std::map<int, SelectionState *> SelectionStates::states;

SelectionState *SelectionStates::state(int type) {
    if (states[type] == nullptr) {
        states[1] = new NumbState(1);
        states[2] = new AwakeState(2);
        states[3] = new LoadState(3);
        states[4] = new ShotState(4);
        states[5] = new OpposedForceShotState(5);
    }
    return states[type];
}