#ifndef ZEROKAN_WT_FLIGHT_RECORDER_HTTP_CLIENT_H
#define ZEROKAN_WT_FLIGHT_RECORDER_HTTP_CLIENT_H

#include <string>

class Http_Client {
 private:
  std::string url;

 public:
  Http_Client(std::string url);
  void get_data(std::string get_request,std::string &data);

};


#endif //ZEROKAN_WT_FLIGHT_RECORDER_HTTP_CLIENT_H
