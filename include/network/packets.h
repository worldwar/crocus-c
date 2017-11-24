#ifndef CROCUS_PACKETS_H
#define CROCUS_PACKETS_H

#include "action.h"
#include "network/packet.h"

class Packets {
public:
    static Packet *packet(const Action &action);

    static Packet *action(uint8_t bytes[]);

    static Action action(const Packet *packet);
};

#endif // CROCUS_PACKETS_H
