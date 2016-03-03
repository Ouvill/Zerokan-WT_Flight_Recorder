#include "async_client.h"
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <iostream>

namespace asio = boost::asio;
using asio::ip::tcp;

AsyncClient::AsyncClient(asio::io_service& io_service , const std::string& server,const std::string port, const std::string& path):
    io_service_(io_service),socket_(io_service), resolver_(io_service), server_(server), path_(path), port_(port) {

  connect(server, port, path);
}




// 接続
void AsyncClient::connect(const std::string& server,const std::string port, const std::string& path) {

  tcp::resolver::query query(server, port);
  resolver_.async_resolve(query, boost::bind(&AsyncClient::on_resolve, this,
  asio::placeholders::error(), asio::placeholders::iterator()));

}

void AsyncClient::on_resolve(const boost::system::error_code& error, boost::asio::ip::tcp::resolver::iterator endpoint_iterator) {
  if (error) {
    std::cout << "resolve failed:" << error.message() << std::endl;
    return;
  }

  // 非同期で接続
  asio::async_connect(
      socket_,
      endpoint_iterator,
      boost::bind(&AsyncClient::on_connect, this, asio::placeholders::error));
}


void AsyncClient::on_connect(const boost::system::error_code &error) {
  if (error) {
    std::cout << "connect failed : " << error.message() << std::endl;
    is_complete_ = false ;
  }
  else {
    send();
  }
}

// メッセージ送信
void AsyncClient::send() {
  std::string send_data_ = "GET " + path_ +" HTTP/1.0\r\n\r\n";
  asio::async_write(
      socket_,
      asio::buffer(send_data_),
      boost::bind(&AsyncClient::on_send, this,
                  asio::placeholders::error,
                  asio::placeholders::bytes_transferred));
}

void AsyncClient::on_send(const boost::system::error_code &error, size_t bytes_transferrerd) {
  if ( error ) {
    std::cout << "send failed:" << error.message() << std::endl;
    is_complete_ = false;
  }

  else {
    start_recieve();
  }
}

// メッセージ受信
void AsyncClient::start_recieve() {
  boost::asio::async_read(socket_, receive_buff_, asio::transfer_all(),
                          boost::bind(&AsyncClient::on_receive, this,
                                      asio::placeholders::error, asio::placeholders::bytes_transferred()));
}


void AsyncClient::on_receive(const boost::system::error_code& error, size_t bytes_transferred)
{
  if (error && error != boost::asio::error::eof) {
    std::cout << "receive failed: " << error.message() << std::endl;
    is_complete_ = false;
  }
  else {
    data_ = asio::buffer_cast<const char*>(receive_buff_.data());
//    std::cout << data << std::endl;

    receive_buff_.consume(receive_buff_.size());

    is_complete_ = true;
  }
}
const std::string& AsyncClient::data() {
  return data_;
}

const std::string AsyncClient::body() {
  std::string body = "";
  std::string::size_type pos = data_.find("\r\n\r\n");
  if( pos!= std::string::npos) {
    body = data_.substr(pos+4);
  }

  return body;
}
bool AsyncClient::is_complete() {
  return is_complete_;
}
