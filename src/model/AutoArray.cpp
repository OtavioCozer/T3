//
// Created by otavio on 03/05/2021.
//

#include "AutoArray.h"

AutoArray::AutoArray(const AutoArray &aarray) {
    array = aarray.array;
    isReleased = aarray.isReleased;
    aarray.isReleased = true;
}

AutoArray::~AutoArray() {
    if (!isReleased && array != nullptr) {
        delete[] array;
    }
}

char *AutoArray::get() const {
    return array;
}

char &AutoArray::operator*() const {
    return *array;
}

AutoArray &AutoArray::operator=(const AutoArray &aarray) {
    if (&aarray != this) {
        if (!isReleased && array != nullptr) {
            delete[] array;
        }
        array = aarray.array;
        isReleased = aarray.isReleased;
        aarray.isReleased = true;
    }

    return *this;
}

char *AutoArray::operator->() const {
    return array;
}

char *AutoArray::release() {
    isReleased = true;
    return array;
}

void AutoArray::reset(char *array_ = nullptr) {
    if (!isReleased && array != nullptr) {
        delete[] array;
    }
    array = array_;
}

char *AutoArray::operator+(int i) {
    return array + i;
}

char &AutoArray::operator[](int i) {
    return array[i];
}
