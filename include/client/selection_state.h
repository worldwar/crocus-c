#ifndef CROCUS_SELECTION_STATE_H
#define CROCUS_SELECTION_STATE_H

#include <map>
#include <network/packet.h>

class GameContext;
class ClientGame;
class Point;
class SelectionState {
protected:
    int _type;

public:
    SelectionState(int type) : _type(type) {}

    virtual SelectionState *awake(GameContext *context) {
        return this;
    };
    virtual SelectionState *numb(GameContext *context) {
        return this;
    };
    virtual SelectionState *finish(GameContext *context) {
        return this;
    }
    virtual SelectionState *handleClick(GameContext *context,
                                        const Point &point) {
        return this;
    }
    virtual SelectionState *handlePacket(GameContext *context,
                                         const Packet *packet) {
        return this;
    }
    int type() const {
        return _type;
    }
};

class NumbState : public SelectionState {
public:
    NumbState(int type);

    SelectionState *awake(GameContext *context) override;

    SelectionState *handlePacket(GameContext *context,
                                 const Packet *packet) override;
};

class AwakeState : public SelectionState {
public:
    AwakeState(int type);

    SelectionState *handleClick(GameContext *context,
                                const Point &point) override;
};

class LoadState : public SelectionState {
public:
    LoadState(int type);
    SelectionState *handleClick(GameContext *context,
                                const Point &point) override;
};

class ShotState : public SelectionState {
private:
    ClientGame *clientGame;

public:
    ShotState(int type);
    SelectionState *finish(GameContext *context) override;
};

class OpposedForceShotState : public SelectionState {
public:
    OpposedForceShotState(int type);
    SelectionState *finish(GameContext *context) override;
};

class SelectionStates {
private:
    static std::map<int, SelectionState *> states;

public:
    static SelectionState *state(int type);
    static SelectionState *numbState() {
        return state(1);
    }
    static SelectionState *awakeState() {
        return state(2);
    }
    static SelectionState *loadState() {
        return state(3);
    }
    static SelectionState *shotState() {
        return state(4);
    }
    static SelectionState *opposedForceShotState() {
        return state(5);
    }
};

#endif // CROCUS_SELECTION_STATE_H
