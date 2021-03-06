#include "network/packet.h"
#include <common.h>

RawPacket ActionPacket::raw() const {
    RawPacket raw;
    raw << 8;
    raw << (uint8_t)common::cast(_type);
    raw << (uint8_t)common::cast(_force);
    raw << (uint8_t)common::cast(_kind);
    raw << (uint8_t)common::cast(_actionType);

    raw << (uint8_t)common::cast(_from.x());
    raw << (uint8_t)common::cast(_from.y());
    raw << (uint8_t)common::cast(_to.x());
    raw << (uint8_t)common::cast(_to.y());
    return raw;
}

RawPacket StartGamePacket::raw() const {
    RawPacket raw;
    raw << 3;
    raw << (uint8_t)common::cast(_type);
    raw << (uint8_t)common::cast(_orderType);
    raw << (uint8_t)common::cast(_force);
    return raw;
}

RawPacket EndGamePacket::raw() const {
    RawPacket raw;
    raw << 4;
    raw << (uint8_t)common::cast(_type);
    raw << (uint8_t)common::cast(_orderType);
    raw << (uint8_t)common::cast(_result);
    raw << (uint8_t)common::cast(_reason);
    return raw;
}

RawPacket UnreadyPacket::raw() const {
    RawPacket raw;
    raw << 2;
    raw << (uint8_t)common::cast(_type);
    raw << (uint8_t)common::cast(_orderType);
    return raw;
}

RawPacket ReadyPacket::raw() const {
    RawPacket raw;
    raw << 2;
    raw << (uint8_t)common::cast(_type);
    raw << (uint8_t)common::cast(_orderType);
    return raw;
}
