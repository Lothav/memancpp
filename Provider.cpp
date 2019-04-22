//
// Created by luiz0tavio on 4/29/18.
//

#include "Provider.hpp"

/* Init static member with a empty map */
std::unique_ptr<mem::Pool> mem::Provider::pool_ = nullptr;

void mem::Provider::initPool(std::size_t size) noexcept
{
    if(checkPool()) {
        std::cerr << "Pool already initialized!" << std::endl;
        return;
    }

    pool_ = std::make_unique<mem::Pool>(size);
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