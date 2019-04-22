#ifndef MEMORY_POOL_HPP
#define MEMORY_POOL_HPP

#include <malloc.h>
#include <iostream>
#include <cstring>
#include <vector>
#include <memory>

namespace mem
{
    template<class T>
    class Pool
    {

    private:

        enum MemStatus {FREE, IN_USE};

        struct MemMap {
            uint      index  = 0;
            MemStatus status = FREE;
        };

        std::vector<MemMap> mem_map_ = {};
        std::vector<std::shared_ptr<T>> mem_pool_ = {};

        std::size_t size_;

    public:

        explicit Pool(std::size_t size);

        std::shared_ptr<T> get();
    };
}

#endif //MEMORY_POOL_HPP
