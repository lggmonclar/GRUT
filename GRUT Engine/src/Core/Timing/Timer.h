#pragma once

#include <chrono>
#include "Core/Debugging/Logger.h"

namespace GRUT {
    class Timer {
        private:
            std::chrono::time_point<std::chrono::steady_clock> p_start, p_end;
            std::chrono::duration<float> p_duration;
            std::string m_name;

        public:
            Timer(std::string p_name = "Timer") {
                m_name = p_name;
                p_start = std::chrono::high_resolution_clock::now();
                p_duration = p_start - p_start;
            }

            ~Timer() {
                p_end = std::chrono::high_resolution_clock::now();
                p_duration = p_end - p_start;
                float ms = p_duration.count() * 1000.0f;
                LOG_INFO("{0} took {1}ms", m_name, ms);
            }
    };
}