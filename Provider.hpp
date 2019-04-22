//
// Created by luiz0tavio on 4/29/18.
//

#ifndef ONYX_PROVIDER_HPP
#define ONYX_PROVIDER_HPP

#include <map>
#include <memory>
#include "Pool.hpp"

namespace mem
{
    class Provider
    {

    private:

        /* Store circular memory pool.*/
        static std::unique_ptr<Pool<T>> pool_;

    public:

        /* Alloc memory pool.
         * Must call destroyPool() to avoid memory leak. */
        static void initPool(std::size_t size) noexcept;

        /* Check pool state. */
        static bool checkPool() noexcept;

        /* Circular buffer-like memory gatherer by PoolType */
        static void* getMemory(std::size_t size) noexcept;
    };
}

#endif //ONYX_PROVIDER_HPP
