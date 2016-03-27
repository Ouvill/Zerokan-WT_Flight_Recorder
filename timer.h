#ifndef ZEROKAN_WT_FLIGHT_RECORDER_TIMER_H
#define ZEROKAN_WT_FLIGHT_RECORDER_TIMER_H

#include <string>
#include <time.h>

class Timer {

 private:
  time_t start_time_;
  time_t end_time_;

 public:
  Timer();
  void stop();

  time_t start_time();
  time_t end_time();

};


#endif //ZEROKAN_WT_FLIGHT_RECORDER_TIMER_H
