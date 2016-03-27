#include "user.h"
#include <fstream>
#include <boost/filesystem.hpp>

Record::Record() {
  kill_count_ = 0;
  death_count_ = 0;
  destroy_count_ = 0;
}

Record::~Record() {
};

int Record::kill_count() {
  return kill_count_;
}
int Record::death_count() {
  return death_count_;
}
int Record::destroy_count() {
  return destroy_count_;
}
double Record::kill_ratio() {
  return static_cast<double>(kill_count_)/death_count_;
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

void Record::export_csv(std::string filename,const time_t time) {
  if (!boost::filesystem::exists(filename)) {
    std::ofstream of(filename, std::ios::app);

    of << "開始時間,キル,デス,地上物破壊数" << std::endl;
    of.close();
  }

  struct tm *tm_st = localtime(&time);
  std::ofstream of(filename, std::ios::app);
  of << tm_st->tm_year << tm_st->tm_mon+1 << tm_st->tm_mday << "_" << tm_st->tm_hour << tm_st->tm_min << tm_st->tm_sec << ",";
  of << kill_count_ << ",";
  of << death_count_ << ",";
  of << destroy_count_ << std::endl;

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



