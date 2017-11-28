#ifndef CROCUS_SPRITES_H
#define CROCUS_SPRITES_H

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <map>
#include <piece.h>

class Sprites {
public:
    static sf::Sprite *redPawn;
    static sf::Sprite *defaultBoard;
    static sf::Texture *pieces;
    static int pieceSize;
    static float pieceScale;
    static std::map<int, sf::Sprite *> pieceMap;
    static sf::Font font;

    static sf::Sprite *createPieceSprite(const Piece *piece);
    static int forceKindHash(const Piece *piece);
    static sf::Sprite *sprite(const Piece *piece);
    static void load();
};

#endif // CROCUS_SPRITES_H
