//
// Created by luiz0tavio on 4/29/18.
//

#ifndef ONYX_ALLOCATOR_HPP
#define ONYX_ALLOCATOR_HPP

#include <cstdlib>
#include <new>
#include <iostream>
#include <limits>
#include "Provider.hpp"

namespace Memory
{
    template <class T>
    struct Allocator {

        typedef T value_type;

    public:

        Allocator() = default;
        template <class U> constexpr
        Allocator(const Allocator<U>&) noexcept {}

        T* allocate(std::size_t size) noexcept
        {
            auto max = std::numeric_limits<size_t>::max() / sizeof(T);
            if(size > max) {
                std::cerr << "ERR: Size: " << std::to_string(size) << "bytes exceeds max." << std::endl;
                return nullptr;
            }

            auto* mem = Provider::getMemory(size*sizeof(T));
            if(auto* p = static_cast<T*>(mem)) return p;
            if(auto* p = (T *) malloc(size)) return p;

            std::cerr << "ERR: Cannot get/alloc memory. Size: " << std::to_string(size) << "bytes." << std::endl;
            return nullptr;
        }

        void deallocate(T* p, std::size_t) noexcept
        {
            // @TODO mark memory as free.
        }
    };

    template <class T, class U>
    bool operator==(const Allocator<T>&, const Allocator<U>&) { return true; }

    template <class T, class U>
    bool operator!=(const Allocator<T>&, const Allocator<U>&) { return false; }
}

#endif //ONYX_ALLOCATOR_HPP
