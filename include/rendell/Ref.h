#pragma once
#include <algorithm>
#include <cstdint>
#include <type_traits>

namespace rendell {
template <typename T> static void releaseDefaultCallback(T *data) {
    if (data) {
        delete[] data;
    }
}

template <typename T> struct ArrayRef {
    static_assert(std::is_trivially_copyable<T>::value,
                  "ArrayRef<T> requires T to be trivially copyable");

    using ReleaseCallback = void (*)(T *data);
    T *data;
    size_t size;
    ReleaseCallback releaseCallback;

    inline void release() {
        if (releaseCallback) {
            releaseCallback(data);
        }
    }
};

template <typename T>
ArrayRef<T>
MakeArrayRef(T *data, size_t size,
             typename ArrayRef<T>::ReleaseCallback releaseCallback = releaseDefaultCallback<T>) {
    static_assert(std::is_trivially_copyable<T>::value,
                  "MakeRef with memcpy requires trivially copyable T");

    ArrayRef<T> ref;
    ref.data = data;
    ref.size = size;
    ref.releaseCallback = releaseCallback;
    return ref;
}

template <typename T>
ArrayRef<T>
AllocArray(const T *data, size_t size,
           typename ArrayRef<T>::ReleaseCallback releaseCallback = releaseDefaultCallback<T>) {
    static_assert(std::is_trivially_copyable<T>::value,
                  "Alloc with memcpy requires trivially copyable T");

    T *newData = new T[size];
    std::memcpy(newData, data, size * sizeof(T));

    ArrayRef<T> ref;
    ref.data = newData;
    ref.size = size;
    return ref;
}
} // namespace rendell