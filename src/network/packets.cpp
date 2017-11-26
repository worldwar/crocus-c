#include "network/packets.h"
#include <common.h>

Packet *Packets::packet(const Action &action) {
    ActionPacket *actionPacket = new ActionPacket{
        action.piece().force(), action.piece().kind(), action.actionType(),
        action.piece().position(), action.target()};
    return actionPacket;
}

Packet *Packets::action(uint8_t *bytes) {
    ActionPacket *packet = new ActionPacket();
    packet->setForce(static_cast<Force>(bytes[1]));
    packet->setKind(static_cast<Kind>(bytes[2]));
    packet->setActionType(static_cast<ActionType>(bytes[3]));
    packet->setFrom(Position{bytes[4], bytes[5]});
    packet->setTo(Position{bytes[6], bytes[7]});
    return packet;
}

Action Packets::action(const Packet *packet) {
    ActionPacket *actionPacket = (ActionPacket *)packet;
    return Action{Piece{actionPacket->force(), actionPacket->kind(),
                        actionPacket->from()},
                  actionPacket->to(), actionPacket->actionType()};
}

OrderPacket *Packets::order(uint8_t *bytes) {
    switch (static_cast<OrderType>(bytes[1])) {
    case OrderType::START_GAME:
        return new StartGamePacket{static_cast<Force>(bytes[2])};
    }
}
