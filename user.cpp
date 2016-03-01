#include "user.h"
Record::Record() {
  kill_count_ = 0;
  death_count_ = 0;
  destroy_count_ = 0;
}

Record::~Record() {};

int Record::kill_count() {
  return kill_count_;
}
int Record::death_count() {
  return death_count_;
}
int Record::destroy_count() {
  return 0;
}
void Record::add_kill_count() {
  kill_count_++;
}
void Record::add_death_count() {
  death_count_++;
}
void Record::add_destroy_count() {
  destroy_count_++;
}


User::User(std::string name) {
  name_ = name;
}

User::~User() {
  delete record_;
}

std::string User::name() {
  return name_;
}

Record *User::record() {
  return record_;
}
void User::reset_record() {
  delete record_;
  record_ = new Record();
}


