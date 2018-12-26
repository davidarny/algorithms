#ifndef ALGORITHMS_INSERTABLE_H
#define ALGORITHMS_INSERTABLE_H

template <typename T>
class Insertable {
public:
    virtual void insert(T value) = 0;
};

#endif //ALGORITHMS_INSERTABLE_H
