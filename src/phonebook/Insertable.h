#ifndef ALGORITHMS_INSERTABLE_H
#define ALGORITHMS_INSERTABLE_H

#include <string>

template <typename K = int>
class Insertable {
public:
    virtual void insert(K key) = 0;
};

#endif //ALGORITHMS_INSERTABLE_H
