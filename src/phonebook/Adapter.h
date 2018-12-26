#ifndef ALGORITHMS_ADAPTER_H
#define ALGORITHMS_ADAPTER_H

template <typename T>
class Adapter {
public:
    virtual T convert() = 0;
};

#endif //ALGORITHMS_ADAPTER_H
