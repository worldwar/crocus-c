#include "client/game_context.h"
#include <network/packets.h>
#include <thread>

ClientGame::ClientGame()
    : game(), clientBoard{game.board(), {42, 52}, 102, Force::BLACK} {
    _player = Force::BLACK;
    selectionState = SelectionStates::state(1);
    context = new GameContext(this, clientBoard);
}

void ClientGame::draw(sf::RenderWindow &window) {
    clientBoard.draw(window, selectionState);
}

void ClientGame::printState() {
    std::cout << "selectionState: " << selectionState->type() << std::endl;
}

void ClientGame::init() {
    sender = new Sender("game.zhuran.tw", 10200);
    sender->init();
    startReceive();
}

void ClientGame::send(const Action &action) {
    Packet *packet = Packets::packet(action);
    sender->send(packet);
    delete packet;
}

void ClientGame::startReceive() {
    std::thread t([&]() {
        while (true) {
            Packet *packet = sender->receive();
            this->handle(packet);
        }
    });
    t.detach();
}

void ClientGame::handle(const Packet *packet) {
    if (packet->type() == PacketType::ACTION) {
        selectionState = selectionState->handlePacket(context, packet);
    } else if (packet->type() == PacketType::ORDER) {
        const OrderPacket *orderPacket =
            dynamic_cast<const OrderPacket *>(packet);
        if (orderPacket->orderType() == OrderType::START_GAME) {
            const StartGamePacket *p =
                dynamic_cast<const StartGamePacket *>(orderPacket);
            begin(p->force());
        }
    }
}

void ClientGame::begin(Force force) {
    game.board().reset();
    clientBoard.setView(force);
    _player = force;
    if (force == Force::RED) {
        selectionState = SelectionStates::awakeState();
    } else {
        selectionState = SelectionStates::numbState();
    }
}
