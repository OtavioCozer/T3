//
// Created by otavio on 03/05/2021.
//

#ifndef T3_AUTOARRAY_H
#define T3_AUTOARRAY_H


class AutoArray {
private:
    char *array;
    mutable bool isReleased;

public:
    explicit AutoArray(char *array_ = nullptr) : array(array_), isReleased(false) {
    }

    AutoArray(const AutoArray &aarray);

    ~AutoArray();

    char *get() const;

    char &operator*() const;

    AutoArray &operator=(const AutoArray &aarray);

    char *operator->() const;

    char *release();

    char *operator+(int i);

    char &operator[](int i);
};


#endif //T3_AUTOARRAY_H
