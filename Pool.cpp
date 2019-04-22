//
// Created by luiz0tavio on 4/29/18.
//

#include "Pool.hpp"

template<class T>
mem::Pool<T>::Pool(std::size_t size) : size_(size)
{
    mem_pool_.resize(size);
    if (mem_pool_.capacity() != size) {
        std::cerr << "Error malloc memory pool" << std::endl;
    }

    mem_map_.resize(size);
    for (int i = 0; i < mem_map_.size(); ++i) {
        mem_map_[i].index = i;
        mem_map_[i].status = FREE;
    }
}

template<class T>
std::shared_ptr<T> mem::Pool<T>::get()
{
    if (mem_pool_.capacity() == 0) {
        std::cerr << "Memory pool not allocated!" << std::endl;
        return nullptr;
    }

    int free_pos = -1;
    for (int i = 0; i < mem_map_.size(); ++i) {
        if(mem_map_[i].status == FREE)
        {
            mem_map_[i].status = IN_USE;
            return mem_pool_[free_pos];
        }
    }

    std::cerr << "No free memory found! Try to increase pool size!" << std::endl;
    return nullptr;
}
