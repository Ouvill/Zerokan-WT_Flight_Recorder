#ifndef ZEROKAN_WT_FLIGHT_RECORDER_ASYNC_CLIENT_H
#define ZEROKAN_WT_FLIGHT_RECORDER_ASYNC_CLIENT_H

#include <boost/asio.hpp>


class AsyncClient {
 private:
  boost::asio::io_service& io_service_;
  boost::asio::ip::tcp::socket socket_;
  boost::asio::streambuf receive_buff_;
  boost::asio::ip::tcp::resolver resolver_;

  bool is_complete_;


  std::string server_;
  std::string port_;
  std::string path_;
  std::string data_;



  void connect(const std::string& server,const std::string port, const std::string& path);
  void on_resolve(const boost::system::error_code& error, boost::asio::ip::tcp::resolver::iterator endpoint_iterator);
  void on_connect(const boost::system::error_code& error);

  void on_send(const boost::system::error_code& error, size_t bytes_transferrerd);
  void start_recieve();
  void on_receive(const boost::system::error_code& error, size_t bytes_transferred);


 public:
  AsyncClient(boost::asio::io_service& io_service,const std::string& server, const std::string port, const std::string& path);
  void send();
  bool is_complete();
  const std::string& data();
  const std::string body();


  void connect();
  void send(std::string path);
};



#endif //ZEROKAN_WT_FLIGHT_RECORDER_ASYNC_CLIENT_H