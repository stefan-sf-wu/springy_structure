#ifndef TIMER_H_
#define TIMER_H_

#include <iostream>
#include <thread>
#include <unistd.h>
#include <chrono>
#include <iomanip>

#include "common.hpp"

const bool k_logger_enabled = false;

const float k_time_step = 0.01;                 // sec
const unsigned int k_max_display_time = 3000;   // sec


class Timer
{
  private:
    float simulation_time_;
    float timestep_;
    float refresh_interval_;
    float next_display_time_;

  public:
    Timer();
    ~Timer();

    void reset(float refresh_interval) {
        timestep_          = k_time_step;
        simulation_time_   = 0.0f;
        refresh_interval_ = refresh_interval;
        next_display_time_ = 0.0f + refresh_interval_;
    }

    float get_simluation_time() {
        return simulation_time_;
    }

    void update_simulation_time() {
        simulation_time_ += k_time_step;
    }

    void update_next_display_time() {
        next_display_time_ += refresh_interval_;
    }
    
    bool is_time_to_draw() {
        return (simulation_time_ >= next_display_time_);
    }

    bool is_time_to_stop() {
        return (simulation_time_ >= k_max_display_time);
    }

#if (k_logger_enabled)
    void logger() {
        std::cout << std::setw(10) << "[timer] ";
        std::cout << "simulation_time: " << simulation_time_ << " | next_display_time: " << next_display_time_ << std::endl;
    }
#endif
};

Timer::Timer() {}
Timer::~Timer() {}
    
#endif
