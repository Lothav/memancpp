//
// Created by luiz0tavio on 4/29/18.
//

#include "Provider.hpp"

/* Init static member with a empty map */
mem::Pool* mem::Provider::pool_ = nullptr;

void mem::Provider::initPool(std::size_t size) noexcept
{
    if(checkPool()) {
        std::cerr << "Pool already initialized!" << std::endl;
        return;
    }

    pool_ = new mem::Pool(size);
}

void* mem::Provider::getMemory(std::size_t size) noexcept
{
    if(!checkPool()) {
        std::cerr << "Pool not initialized!" << std::endl;
        return nullptr;
    }

    return pool_->get(size);
}

bool mem::Provider::checkPool() noexcept
{
    return pool_ != nullptr;
}

void mem::Provider::destroyPool() noexcept
{
    if(!checkPool()) {
        std::cerr << "Cannot destroy a Pool! (not initialized)" << std::endl;
        return;
    }

    delete pool_;
    pool_ = nullptr;
};
