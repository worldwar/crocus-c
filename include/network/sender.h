#ifndef CROCUS_SENDER_H
#define CROCUS_SENDER_H

#include "network/packet.h"
#include <SFML/Network.hpp>
#include <string>

class Sender {
private:
    std::string _remote;
    int _port;
    sf::TcpSocket _socket;

public:
    Sender(std::string remote, int _port);
    bool init();
    void send(const Packet *packet);
    Packet *receive();
};

#endif // CROCUS_SENDER_H
