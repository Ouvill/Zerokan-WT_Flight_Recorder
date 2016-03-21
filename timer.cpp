#include "timer.h"

Timer::Timer() {
  start_time_ = time(NULL);

}

void Timer::stop() {
  end_time_ = time(NULL);
}


time_t Timer::start_time() {
  return start_time_;
}


time_t Timer::end_time() {
  return end_time_;
}
