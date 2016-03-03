#ifndef ZEROKAN_WT_FLIGHT_RECORDER_USER_H
#define ZEROKAN_WT_FLIGHT_RECORDER_USER_H

#include <string>
#include "timer.h"

class Record {
 private:
  int kill_count_;
  int death_count_;
  int destroy_count_;


 public:
  Record();
  ~Record();

  int kill_count();
  int death_count();
  int destroy_count();

  void add_kill_count();
  void add_death_count();
  void add_destroy_count();
};


class User {
 private:
  std::string name_;
  Record* record_;

 public:
  User(std::string name);
  ~User();
  std::string name();
  Record* record();

  void reset_record();
};



#endif //ZEROKAN_WT_FLIGHT_RECORDER_USER_H
