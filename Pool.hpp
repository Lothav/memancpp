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

        explicit Pool(std::size_t size)
        {
            // allocate pool
            mem_pool_ = new T[size];
            if (mem_pool_== nullptr) {
                std::cerr << "Error malloc memory pool" << std::endl;
            }

            for (int i = 0; i < size; ++i) {
                mem_map_[mem_pool_+i] = FREE;
            }
        }

        ~Pool()
        {
            delete[] mem_pool_;
        }

        void* get()
        {
            if (mem_pool_ == nullptr) {
                std::cerr << "Memory pool not allocated!" << std::endl;
                return nullptr;
            }

            for (auto& it = mem_map_.begin(); it != mem_map_.end(); it++) {
                if(it->second == FREE) {
                    it->second = IN_USE;
                    return it->first;
                }
            }

            std::cerr << "No free memory found! Try to increase pool size!" << std::endl;
            return nullptr;
        }

        void free(void * ptr)
        {
            mem_map_[ptr] = FREE;
        };
    };
}

#endif //MEMORY_POOL_HPP
