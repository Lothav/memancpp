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
        std::map<T*, MemStatus> mem_map_ = {};

        std::size_t initial_size_;
        uint32_t mem_increases_count_ = 0;

    public:

        explicit Pool(std::size_t initial_size) : initial_size_(initial_size > 0 ? initial_size : 1)
        {
            // allocate initial pool
            increasePool();
        }

        ~Pool()
        {
            std::free(mem_pool_);
        }

        void increasePool()
        {
            mem_increases_count_++;
            mem_pool_ = (T *) std::realloc(mem_pool_, getPoolSize());
            if (mem_pool_ == nullptr) {
                std::cerr << "Error malloc memory pool" << std::endl;
            }

            for (size_t i = initial_size_ * (mem_increases_count_-1); i < initial_size_ * mem_increases_count_; ++i) {
                mem_map_[&mem_pool_[i]] = FREE;
            }
        }

        std::size_t getPoolSize()
        {
            return initial_size_ * mem_increases_count_ * sizeof(T);
        }

        void* getMemory()
        {
            for (auto it = mem_map_.begin(); it != mem_map_.end(); it++) {
                if(it->second == FREE) {
                    it->second = IN_USE;
                    return (void *) it->first;
                }
            }

            std::cerr << "No free memory found in Pool of type '" << typeid(T).name() << "' with size " << std::to_string(getPoolSize()) << "!" << std::endl;
            std::cerr << "Trying to increase pool size... ";
            increasePool();
            std::cerr << "Success! New size: " << std::to_string(getPoolSize()) << "." << std::endl;

            return getMemory();
        }

        void free(void * ptr)
        {
            mem_map_[(T *) ptr] = FREE;
        }

        void clear()
        {
            for (auto it = mem_map_.begin(); it != mem_map_.end(); it++) {
                it->second = FREE;
            }
        }
    };
}

#endif //MEMORY_POOL_HPP
