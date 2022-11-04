#pragma once

#include <rose/hash.h>
//#include <cstddef>

namespace rose {
    struct SingletonRegister {
        virtual void * VLazeRegister(size_t size, rose::hash_value hash, void (*)(void *), void (*)(void *)) = 0;

        template<class T>
        T & Get() {
            void * ptr = VLazeRegister(
                //Register the size
                sizeof(T), 
                //Type id hash
                rose::type_id<T>::VALUE,
                //Function pointer to constructor
                +[](void * data) {
                    new T::T(data)();
                }, 
                //Function pointer to destructor
                +[](void * data) {
                    T::~T(data)();
                }
            );

            T * tptr = std::reinterpret_cast<T*>(ptr);
            return *tptr;
        }
    };
}
