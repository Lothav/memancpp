#ifndef MEMORY_POOL_HPP
#define MEMORY_POOL_HPP

#include <malloc.h>
#include <iostream>
#include <cstring>
#include <vector>
#include <memory>
#include <map>

namespace mem
{
    template<class T>
    class Pool
    {

    private:

        enum MemStatus {FREE, IN_USE};

        T* mem_pool_ = nullptr;
        std::map<void *, MemStatus> mem_map_ = {};

        std::size_t size_;

    public:

        explicit Pool(std::size_t size);
        ~Pool();

        void* get();
        void free(void *);
    };
}

#endif //MEMORY_POOL_HPP
