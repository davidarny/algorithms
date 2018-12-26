#ifndef ALGORITHMS_INITABLE_H
#define ALGORITHMS_INITABLE_H

template <typename T, typename P>
class Initable {
public:
    virtual P init(T args) = 0;
};

#endif //ALGORITHMS_INITABLE_H
