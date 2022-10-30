#ifndef TIMER_H_
#define TIMER_H_

#define ENABLE_LOGGER false

#include <iostream>
#include <thread>
#include <unistd.h>
#include <chrono>
#include <iomanip>

#include "Common.hpp"

const float k_time_step = 0.01;              // sec
const unsigned k_max_display_time = 3000;    // sec


class Timer
{
  private:
    float simulation_time_;
    float timestep_;
    float next_display_time_;

  public:
    Timer();
    ~Timer();

    void reset() {
        timestep_          = k_time_step;
        simulation_time_   = 0;
        next_display_time_ = DISPLAY_REFRESH_INTERVAL;
    }

    float get_simluation_time() {
        return simulation_time_;
    }

    void update_simulation_time() {
        simulation_time_ += k_time_step;
    }

    void update_next_display_time() {
        next_display_time_ += DISPLAY_REFRESH_INTERVAL;
    }
    
    bool is_time_to_draw() {
        return (simulation_time_ >= next_display_time_);
    }

    bool is_time_to_stop() {
        return (simulation_time_ >= k_max_display_time);
    }

#if ENABLE_LOGGER
    void logger() {
        std::cout << std::setw(10) << "[timer] ";
        std::cout << "simulation_time: " << simulation_time_ << " | next_display_time: " << next_display_time_ << std::endl;
    }
#endif
};

Timer::Timer() {}
Timer::~Timer() {}
    
#endif
