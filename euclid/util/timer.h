#pragma once
#include <chrono>

class Timer {
public:
  Timer() = default;
  ~Timer() = default;

  void Start() {
    t1_ = std::chrono::high_resolution_clock::now();
  }

  float Stop() {
    t2_ = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> d = t2_ - t1_;
    return d.count();
  }

  float StopStart() {
    const float result = Stop();
    t1_ = t2_;
    return result;
  }

private:
  std::chrono::time_point<std::chrono::high_resolution_clock> t1_, t2_;
};


// #include <thread>
// #include <chrono>
//     Timer timer;
//     timer.Start();
    
//     std::this_thread::sleep_for(500ms);
//     float t = timer.StopStart();
//     spdlog::info("timer start stop: {:.3f}", t);

//     std::this_thread::sleep_for(400ms);
//     t = timer.Stop();
//     spdlog::info("timer stop: {:.3f}", t);