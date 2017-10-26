#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window.hpp>
#include <client/client_board.h>

int main() {
    sf::RenderWindow window(sf::VideoMode(550, 640), "crocus");

    sf::Texture texture;

    Board board = Board();
    board.reset();
    domain::load();
    ClientBoard clientBoard{board, {42, 52}, 102, Force::RED};

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        clientBoard.draw(window);
        window.display();
    }
    return 0;
}