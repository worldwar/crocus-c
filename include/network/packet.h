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

#endif // CROCUS_PACKET_H
