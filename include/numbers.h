#ifndef CROCUS_NUMBERS_H
#define CROCUS_NUMBERS_H

#include <list>

class Numbers {
public:
    static std::list<int> range(int from, int to,
                                bool include_endpoints = false);
};

#endif // CROCUS_NUMBERS_H
