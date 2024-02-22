#pragma once

#include <Clod/System/Type.hpp>

namespace Clod
{
    template<typename Base, typename T>
    bool instanceof(const T *ptr)
    {
        return dynamic_cast<const Base *>(ptr) != nullptr;
    }
}
