#ifndef CROCUS_GAME_H
#define CROCUS_GAME_H

#include "board.h"
#include <chrono>

class Game {
private:
    Board _board;
    GameState _state;
    GameResult _result;
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
        win(opposed(force));
    }

    void draw() {
        endGame(GameResult::DRAW);
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
            win(_turn);
        }
    }

    void endGame(GameResult result) {
        _result = result;
        _state = GameState::ENDED;
    }

    void win(Force force) {
        if (force == Force::RED) {
            endGame(GameResult::RED_WIN);
        } else {
            endGame(GameResult::BLACK_WIN);
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
