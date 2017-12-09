#include "client/game_context.h"
#include <network/packets.h>
#include <thread>

ClientGame::ClientGame()
    : game(), clientBoard{game.board(), {113, 113}, 140, Force::BLACK},
      boardPosition{200, 0}, _controlBoard(this) {
    _player = Force::BLACK;
    selectionState = SelectionStates::state(1);
    context = new GameContext(this, clientBoard);
}

void ClientGame::draw(sf::RenderWindow &window) {
    clientBoard.draw(window, boardPosition, selectionState);
    _controlBoard.draw(window);
}

void ClientGame::printState() {
    std::cout << "selectionState: " << selectionState->type() << std::endl;
}

void ClientGame::init() {
    sender = new Sender("localhost", 10200);
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
        } else if (orderPacket->orderType() == OrderType::END_GAME) {
            const EndGamePacket *p =
                dynamic_cast<const EndGamePacket *>(orderPacket);
            end(p->result(), p->reason());
        }
    }
}

void ClientGame::begin(Force force) {
    _player = force;
    clientBoard.setView(force);
    if (force == Force::RED) {
        selectionState = SelectionStates::awakeState();
    } else {
        selectionState = SelectionStates::numbState();
    }
    game.start();
}

void ClientGame::end(GameResult result, GameEndReason reason) {
    using namespace std::chrono_literals;
    if ((result == GameResult::RED_WIN && player() == Force::RED) ||
        (result == GameResult::BLACK_WIN && player() == Force::BLACK)) {
        showText(L"大吉大利，晚上吃鸡");
    } else if (result == GameResult::DRAW) {
        showText(L"平局");
    } else {
        showText(L"您输了，再接再厉");
    }
    std::this_thread::sleep_for(5s);
    reset();
}

void ClientGame::reset() {
    game.reset();
    clientBoard.reset();
    _controlBoard.reset();
    selectionState = SelectionStates::state(1);
}

void ClientGame::showText(const std::wstring &text) {
    clientBoard.setText(text);
}

void ClientGame::ready() {
    ReadyPacket *packet = Packets::ready();
    sender->send(packet);
    delete packet;
}

void ClientGame::unready() {
    UnreadyPacket *packet = Packets::unready();
    sender->send(packet);
    delete packet;
}
