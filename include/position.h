#ifndef CROCUS_POSITION_H
#define CROCUS_POSITION_H

class Position {
private:
    int _x;
    int _y;

public:
    Position(int x, int y) :
            _x(x),
            _y(y) {

    }

    int x() const {
        return _x;
    }

    int y() const {
        return _y;
    }

    bool xin(int a, int b) const {
        if (a > b) {
            return xin(b, a);
        } else {
            return _x >= a && _x <= b;
        }
    }

    bool yin(int a, int b) const {
        if (a > b) {
            return yin(b, a);
        } else {
            return _y >= a && _y <= b;
        }
    }

    Position move(int dx, int dy) const {
        return Position(_x + dx, _y + dy);
    }

    bool operator==(const Position &position) const {
        return _x == position._x && _y == position._y;
    }

    bool legal() const {
        return _x >= 1 &&
               _x <= 9 &&
               _y >= 1 &&
               _y <= 10;
    }

    bool in_line(const Position& position) const {
        return _x == position._x && _y == position._y;
    }
};

#endif //CROCUS_POSITION_H
