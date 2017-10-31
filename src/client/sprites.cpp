#include "client/sprites.h"
#include <SFML/Graphics/Texture.hpp>
#include <common.h>

sf::Sprite *Sprites::redPawn = nullptr;
sf::Sprite *Sprites::defaultBoard = nullptr;
sf::Texture *Sprites::pieces = nullptr;
int Sprites::pieceSize = 300;
float Sprites::pieceScale = 0.26;
std::map<int, sf::Sprite *> Sprites::pieceMap;

sf::Sprite *Sprites::createPieceSprite(const Piece *piece) {
    int x = (common::cast(piece->kind()) - 1) * pieceSize;
    int y = (common::cast(piece->force()) - 1) * pieceSize;
    sf::IntRect rect{x, y, pieceSize, pieceSize};
    auto *sprite = new sf::Sprite(*pieces, rect);
    sprite->setOrigin(pieceSize / 2.0f, pieceSize / 2.0f);
    sprite->setScale(pieceScale, pieceScale);
    return sprite;
}

int Sprites::forceKindHash(const Piece *piece) {
    return 100 * common::cast(piece->force()) + common::cast(piece->kind());
}

sf::Sprite *Sprites::sprite(const Piece *piece) {
    int hash = forceKindHash(piece);
    sf::Sprite *sprite = pieceMap[hash];
    if (sprite == nullptr) {
        sprite = createPieceSprite(piece);
        pieceMap[hash] = sprite;
    }
    return sprite;
}

void Sprites::load() {
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

    pieces = new sf::Texture;
    pieces->loadFromFile("resources/images/pieces.png");
    pieces->setSmooth(true);
}
