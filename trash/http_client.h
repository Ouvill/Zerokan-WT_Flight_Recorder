#ifndef ZEROKAN_WT_FLIGHT_RECORDER_HTTP_CLIENT_H
#define ZEROKAN_WT_FLIGHT_RECORDER_HTTP_CLIENT_H

#include <string>
#include <boost/asio/io_service.hpp>
#include <boost/asio.hpp>

namespace boost{
  namespace asio {
    class io_service;

    namespace ip {
      namespace tcp {
        class socket;

      };
    };
  };
};

class HttpClient {
 private:
  boost::asio::io_service& io_service_;
  boost::asio::ip::tcp::socket socket_;
  std::string send_data_;  // 送信データ


  std::string url_;
  int port_;

 public:
  HttpClient(std::string url);
  bool get_data(std::string get_request, std::string &data);

};


#endif //ZEROKAN_WT_FLIGHT_RECORDER_HTTP_CLIENT_H
