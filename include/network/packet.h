#ifndef CROCUS_PACKET_H
#define CROCUS_PACKET_H

#include <SFML/Network/Packet.hpp>
#include <cstdint>
#include <enums.h>
#include <position.h>
#include <vector>

using RawPacket = sf::Packet;

enum class PacketType {
    AUTH = 1,
    HEARTBEAT = 2,
    ACTION = 3,
    ORDER = 4,
    MESSAGE = 5
};

enum class OrderType { START_GAME = 1, END_GAME = 2, READY = 3, UNREADY = 4 };

class Packet {
protected:
    PacketType _type;

public:
    Packet(PacketType type) : _type(type) {}

    PacketType type() const {
        return _type;
    }

    void setType(PacketType type) {
        _type = type;
    }

    virtual RawPacket raw() const = 0;
    virtual ~Packet() {}
};

class ActionPacket : public Packet {
private:
    Force _force;
    Kind _kind;
    ActionType _actionType;
    Position _from;
    Position _to;

public:
    ActionPacket() : Packet(PacketType::ACTION) {}
    ActionPacket(Force force, Kind kind, ActionType actionType,
                 const Position &from, const Position &to)
        : Packet(PacketType::ACTION), _force(force), _kind(kind),
          _actionType(actionType), _from(from), _to(to) {}
    RawPacket raw() const override;

    Force force() const {
        return _force;
    }

    void setForce(Force force) {
        _force = force;
    }

    Kind kind() const {
        return _kind;
    }

    void setKind(Kind kind) {
        _kind = kind;
    }

    ActionType actionType() const {
        return _actionType;
    }

    void setActionType(ActionType actionType) {
        _actionType = actionType;
    }
    Position from() const {
        return _from;
    }

    void setFrom(const Position &from) {
        _from = from;
    }
    Position to() const {
        return _to;
    }

    void setTo(const Position &to) {
        _to = to;
    }
};

class OrderPacket : public Packet {
protected:
    OrderType _orderType;

public:
    OrderPacket(OrderType orderType)
        : Packet(PacketType::ORDER), _orderType(orderType) {}

    OrderType orderType() const {
        return _orderType;
    }
};

class StartGamePacket : public OrderPacket {
private:
    Force _force;

public:
    StartGamePacket(Force force)
        : OrderPacket(OrderType::START_GAME), _force(force) {}

    RawPacket raw() const override;

    Force force() const {
        return _force;
    }
};

class EndGamePacket : public OrderPacket {
private:
    GameResult _result;
    GameEndReason _reason;

public:
    EndGamePacket(GameResult result, GameEndReason reason)
        : OrderPacket(OrderType::END_GAME), _result(result), _reason(reason) {}

    RawPacket raw() const override;

    GameResult result() const {
        return _result;
    }

    GameEndReason reason() const {
        return _reason;
    }
};

class ReadyPacket : public OrderPacket {
public:
    ReadyPacket() : OrderPacket(OrderType::READY) {}

    RawPacket raw() const override;
};

class UnreadyPacket : public OrderPacket {
public:
    UnreadyPacket() : OrderPacket(OrderType::UNREADY) {}

    RawPacket raw() const override;
};
#endif // CROCUS_PACKET_H
