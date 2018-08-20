#ifndef MEMORY_POOL_HPP
#define MEMORY_POOL_HPP

#include <malloc.h>
#include <iostream>
#include <cstring>
#include <array>

namespace Memory
{
    class Pool
    {

    private:

        void* mem_pool_;
        unsigned int pos_;
        std::size_t size_;

    public:

        explicit Pool(std::size_t size);

        ~Pool();

        void* get(std::size_t);
    };
}

#endif //MEMORY_POOL_HPP
