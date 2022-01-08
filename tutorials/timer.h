#pragma once

#include <chrono>

/* Allows us to write durations with the unit, e.g. 1s, 30ms, 42ns, ... */
using namespace std::chrono_literals;

using Clock = std::chrono::high_resolution_clock;
using Time = std::chrono::time_point<Clock>;
using Duration = std::chrono::duration<float>;