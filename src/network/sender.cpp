#include <common.h>

#include "network/packets.h"
#include "network/sender.h"

bool Sender::init() {
    sf::Socket::Status status = _socket.connect(_remote, _port);
    return status == sf::Socket::Done;
}

Sender::Sender(std::string remote, int port)
    : _remote(std::move(remote)), _port(port) {}

void Sender::send(const Packet *packet) {
    RawPacket raw = packet->raw();
    size_t size;
    _socket.send(raw.getData(), raw.getDataSize(), size);
}

Packet *Sender::receive() {
    uint8_t lengthBytes[4];
    size_t received;
    _socket.receive(lengthBytes, 4, received);
    int length = common::toInt(lengthBytes);
    uint8_t *bytes = new uint8_t[length];
    _socket.receive(bytes, length, received);

    Packet *packet = nullptr;
    switch (static_cast<PacketType>(bytes[0])) {
    case PacketType::ACTION:
        packet = Packets::action(bytes);
        break;
    case PacketType::ORDER:
        packet = Packets::order(bytes);
        break;
    }
    delete[] bytes;
    return packet;
}
