#ifndef ALGORITHMS_INSERTABLE_H
#define ALGORITHMS_INSERTABLE_H

#include <string>

template <typename K = int, typename V = const std::string&>
class Insertable {
public:
    virtual void insert(K key) = 0;

    virtual void insert(K key, V value) = 0;
};

#endif //ALGORITHMS_INSERTABLE_H
