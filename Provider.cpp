//
// Created by luiz0tavio on 4/29/18.
//

#include "Provider.hpp"

/* Init static member with a empty map */
Memory::Pool* Memory::Provider::pool_ = nullptr;

void Memory::Provider::initPool(std::size_t size) noexcept
{
    if(checkPool()) {
        std::cerr << "Pool already initialized!" << std::endl;
        return;
    }

    pool_ = new Memory::Pool(size);
}

void* Memory::Provider::getMemory(std::size_t size) noexcept
{
    if(!checkPool()) {
        std::cerr << "Pool not initialized!" << std::endl;
        return nullptr;
    }

    return pool_->get(size);
}

bool Memory::Provider::checkPool() noexcept
{
    return pool_ != nullptr;
}

void Memory::Provider::destroyPool() noexcept
{
    if(!checkPool()) {
        std::cerr << "Cannot destroy a Pool! (not initialized)" << std::endl;
        return;
    }

    delete pool_;
    pool_ = nullptr;
};
