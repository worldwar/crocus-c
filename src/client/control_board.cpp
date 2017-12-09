#include "client/client_game.h"
#include <client/gui/imgui/imgui.h>

void ControlBoard::draw(sf::RenderWindow &window) {
    ImGui::SFML::Update(window, _texture, _deltaClock.restart());
    ImGui::Begin("Sample window", NULL, ImVec2(100.f, 100.f), 0.0f,
                 ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
                     ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse |
                     ImGuiWindowFlags_NoSavedSettings);
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0.8f, 0.3f, 0.1f, 1.f});

    if (_game->state() == GameState::NOT_STARTED) {
        if (ImGui::Button(_ready ? "Unready" : "Ready", {80, 40})) {
            _ready = !_ready;
            if (_ready) {
                _game->ready();
            } else {
                _game->unready();
            }
        }
    }
    ImGui::PopStyleColor(1);
    ImGui::End();
    _texture.clear({120, 64, 32});
    ImGui::SFML::Render(_texture);
    sf::Sprite sprite(_texture.getTexture());
    window.draw(sprite);
    _texture.display();
}