#include "Pool.hpp"

template<class T>
mem::Pool<T>::Pool(std::size_t size) : size_(size)
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

template<class T>
mem::Pool<T>::~Pool()
{
    delete[] mem_pool_;
}

template<class T>
void * mem::Pool<T>::get()
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

template<class T>
void mem::Pool<T>::free(void * ptr)
{
    mem_map_[ptr] = FREE;
}
