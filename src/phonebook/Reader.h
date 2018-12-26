#ifndef ALGORITHMS_READER_H
#define ALGORITHMS_READER_H

template <typename T>
class Reader {
protected:
    T mContent;

public:
    virtual T get() = 0;

    virtual void clear() = 0;
};

#endif //ALGORITHMS_READER_H
