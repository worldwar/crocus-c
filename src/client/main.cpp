#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window.hpp>
#include <client/client_board.h>
#include <client/client_game.h>

int main() {
    sf::RenderWindow window(sf::VideoMode(550, 640), "crocus");

    sf::Texture texture;

    domain::load();

    ClientGame game;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed) {
                game.handle(event);
            }
        }
        window.clear();
        game.draw(window);
        window.display();
    }
    return 0;
}