#ifndef CROCUS_CLIENT_DOMAIN_H
#define CROCUS_CLIENT_DOMAIN_H

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace domain {
    static sf::Sprite *redPawn = nullptr;
    static sf::Sprite *defaultBoard = nullptr;
    static void load() {
        sf::Texture *texture = new sf::Texture;
        texture->loadFromFile("resources/images/black-bishop.png");
        texture->setSmooth(true);
        redPawn = new sf::Sprite(*texture);
        redPawn->setOrigin(130, 130);
        redPawn->setScale(0.3, 0.3);

        sf::Texture *texture2 = new sf::Texture;
        texture2->loadFromFile("resources/images/board.jpg");
        texture2->setSmooth(true);
        defaultBoard = new sf::Sprite(*texture2);
    }
} // namespace domain

#endif // CROCUS_CLIENT_DOMAIN_H
