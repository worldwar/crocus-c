#include "client/gui/imgui/imgui-sfml.h"
#include "client/gui/imgui/imgui.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window.hpp>
#include <client/client_board.h>
#include <client/client_game.h>
#include <client/control_board.h>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 640), "crocus");

    sf::Color bgColor;

    float color[3] = {0.f, 0.f, 0.f};
    sf::Texture texture;

    Sprites::load();

    ClientGame game;

    game.init();

    ImGui::SFML::Init(window);
    TimePoint _start = Clock::now();
    TimePoint _frameStart = _start;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);
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
            window.clear({120, 64, 32});
            game.draw(window);
            window.display();
            _frameStart = _frameStart + interval;
        }
    }
    return 0;
}