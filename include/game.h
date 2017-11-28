#ifndef CROCUS_GAME_H
#define CROCUS_GAME_H

#include "board.h"
#include <chrono>

class Game {
private:
    Board _board;
    GameState _state;
    GameResult _result;
    GameEndReason _reason;
    Force _turn;
    TimePoint _startDate;
    TimePoint _turnStartDate;
    Duration _redUsedTime;
    Duration _blackUsedTime;

public:
    Game()
        : _board(), _state(GameState::NOT_STARTED), _redUsedTime(0),
          _blackUsedTime(0) {}

    void start();

    bool play(const Position &from, const Position &to);

    void move(const Position &from, const Position &to);

    bool play(const Piece *piece, const Position &position);

    void resign(Force force) {
        win(opposed(force), GameEndReason::RESIGN);
    }

    void draw(Force force) {
        if (force == Force::RED) {
            endGame(GameResult::DRAW, GameEndReason::RED_DRAW);
        } else {
            endGame(GameResult::DRAW, GameEndReason::BLACK_DRAW);
        }
    }

    TimePoint startDate() const {
        return _startDate;
    }

    TimePoint turnStartDate() const {
        return _turnStartDate;
    }

    Force turn() const {
        return _turn;
    }

    Duration forceUsedTime(Force force) const {
        if (force == Force::RED) {
            return _redUsedTime;
        } else {
            return _blackUsedTime;
        }
    }

    GameResult result() const {
        return _result;
    }

    bool ended() {
        return _state == GameState::ENDED;
    }

    Board &board() {
        return _board;
    }

    void reset() {
        _board.clear();
        _state = GameState::NOT_STARTED;
    }

private:
    void next() {
        settle();
        if (!ended()) {
            turnNext();
        }
    }

    void settle() {
        bool checkmated = _board.checkmated(opposed(_turn));
        if (checkmated) {
            win(_turn, GameEndReason::CHECKMATE);
        }
    }

    void endGame(GameResult result, GameEndReason reason) {
        _result = result;
        _state = GameState::ENDED;
        _reason = reason;
    }

    void win(Force force, GameEndReason reason) {
        if (force == Force::RED) {
            endGame(GameResult::RED_WIN, reason);
        } else {
            endGame(GameResult::BLACK_WIN, reason);
        }
    }

    void turnNext() {
        TimePoint now = Clock::now();
        Duration duration = common::duration(now, _turnStartDate);
        addUsedTime(_turn, duration);
        _turn = opposed(_turn);
        _turnStartDate = now;
    }

    void addUsedTime(Force turn, Duration duration) {
        if (turn == Force::RED) {
            _redUsedTime += duration;
        } else {
            _blackUsedTime += duration;
        }
    }
};

#endif // CROCUS_GAME_H
