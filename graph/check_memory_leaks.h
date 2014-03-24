#pragma once

#include <Windows.h>

void CheckMemoryLeak()
{
    if (_CrtDumpMemoryLeaks())
        throw std::runtime_error("Memory leaks");
}
