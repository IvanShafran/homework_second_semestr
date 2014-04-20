#pragma once

#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

namespace {
    class MemoryMonitor {
        _CrtMemState memory_state_;

    public:
        MemoryMonitor()
        {
            Checkpoint();
        }

        void Checkpoint()
        {
            _CrtMemCheckpoint(&memory_state_);
        }

        bool CheckMemoryLeaks()
        {
            _CrtMemState current_memory_state;
            _CrtMemCheckpoint(&current_memory_state);

            _CrtMemState memory_difference;
            return _CrtMemDifference(&memory_difference, &memory_state_,
                &current_memory_state) != 0;
        }

        size_t GetDifference()
        {
            _CrtMemState current_memory_state;
            _CrtMemCheckpoint(&current_memory_state);

            _CrtMemState memory_difference;
            _CrtMemDifference(&memory_difference, &memory_state_,
                &current_memory_state);

            return memory_difference.lTotalCount;
        }
    };
}
