#ifndef ZEROKAN_WT_FLIGHT_RECORDER_HUBMSG_READER_H
#define ZEROKAN_WT_FLIGHT_RECORDER_HUBMSG_READER_H

#include <string>
#include <vector>
#include "picojson.hpp"
#include "damages.h"

namespace boost{
    namespace asio{
      class io_service;
    };
};

class AsyncClient;

class HudmsgReader {

 private:
  int lastEvt_ = 0;
  int lastDmg_ = 0;
  int get_damages_array(std::string json, picojson::array &json_array);
  boost::asio::io_service *io_service_;
  AsyncClient *client_;
 public:
  static const int ERROR_CODE = -1;

  HudmsgReader();
  ~HudmsgReader();
  bool get_damages(Damages& damages);
  bool connect();



};

#endif //ZEROKAN_WT_FLIGHT_RECORDER_HUBMSG_READER_H
