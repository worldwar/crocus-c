#ifndef CROCUS_POINT_H
#define CROCUS_POINT_H

class Point {
private:
    float _x;
    float _y;

public:
    Point(float x, float y) : _x(x), _y(y) {}

    float x() const {
        return _x;
    }
    float y() const {
        return _y;
    }

    Point move(float deltaX, float deltaY) const {
        return Point(_x + deltaX, _y + deltaY);
    }
};

#endif // CROCUS_POINT_H
