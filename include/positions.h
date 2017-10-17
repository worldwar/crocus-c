#ifndef CROCUS_POSITIONS_H
#define CROCUS_POSITIONS_H

class Position;
class Positions {
public:
    static std::list<Position> range(const Position &from, const Position &to);
};

#endif //CROCUS_POSITIONS_H
