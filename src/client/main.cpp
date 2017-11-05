#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window.hpp>
#include <client/client_board.h>
#include <client/client_game.h>

int main() {
    sf::RenderWindow window(sf::VideoMode(550, 640), "crocus");

    sf::Texture texture;

    Sprites::load();

    ClientGame game;

    TimePoint _start = Clock::now();
    TimePoint _frameStart = _start;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed) {
                game.handle(event);
            }
        }
        auto now = Clock::now();

        auto duration = now - _frameStart;
        const auto interval = Duration(1000000 / 120);
        if (duration > interval) {
            window.clear();
            game.draw(window);
            window.display();
            _frameStart = _frameStart + interval;
        }
    }
    return 0;
}