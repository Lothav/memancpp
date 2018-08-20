//
// Created by luiz0tavio on 4/29/18.
//

#include "Pool.hpp"

mem::Pool::Pool(std::size_t size)
{
    size_     = size;
    mem_pool_ = nullptr;
    pos_      = 0;

    mem_pool_ = std::malloc(size);
    if (mem_pool_ == nullptr) {
        std::cerr << "Error malloc memory pool" << std::endl;
    }
}

mem::Pool::~Pool()
{
    if (mem_pool_ == nullptr) {
        std::cerr << "Memory pool not allocated!" << std::endl;
        return;
    }

    std::free(mem_pool_);
}

void* mem::Pool::get(std::size_t size)
{
    if (mem_pool_ == nullptr) {
        std::cerr << "Memory pool not allocated!" << std::endl;
        return nullptr;
    }

    if (pos_+size > size_) pos_ = 0;

    void *pointer = (uint8_t*)(mem_pool_ + pos_);
    pos_ += size;

    return pointer;
}
