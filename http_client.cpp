//参考 http://nekko1119.hatenablog.com/entry/2013/10/02/145532

#include "http_client.h"
#include <boost/asio.hpp>
#include <iostream>

using namespace std;
namespace asio = boost::asio;
namespace ip = asio::ip;


HttpClient::HttpClient(std::string url) {
  this->url_ = url;


}
void HttpClient::get_data(std::string get_request, std::string &dst_data) {
  try
  {
    asio::io_service io_service;

    //TCPソケットを作成する
    ip::tcp::socket sock(io_service);

    //名前解決(ホスト名からIPアドレスに変換)する
    ip::tcp::resolver resolver(io_service);
    ip::tcp::resolver::query query("localhost", "http");

    //ホスト情報を設定する
//    ip::tcp::endpoint endpoint(*resolver.resolve(query));
    ip::tcp::endpoint endpoint(asio::ip::address::from_string("127.0.0.1"), 8111);

    //ソケットへ接続
    sock.connect(endpoint);

    //メッセージを送信
//    std::string get_request_string = "GET " + get_request + " HTTP/1.0\r\n\r\n"

    asio::streambuf request;
    ostream request_ostream(&request);
    request_ostream << "GET " << get_request << " HTTP/1.0\r\n\r\n";
//    request_ostream << "GET /ohmi_bus/tim_dsp.asp?projCd=1&eigCd=2&teicd=3314&KaiKbn=NOW&pole=1 HTTP/1.0\r\n\r\n";
    asio::write(sock, request);

    //メッセージを受信
    asio::streambuf buffer;
    boost::system::error_code error;
    asio::read(sock, buffer, asio::transfer_all(), error);
    if ( error && error != asio::error::eof)
    {
      std::cout << "receive failed : " << error.message() << std::endl;
    }
    else
    {
      const std::string data(asio::buffer_cast<const char*>(buffer.data()), buffer.size());

      std::string::size_type pos = data.find("\r\n\r\n");
      if( pos!= std::string::npos) {
        dst_data=data.substr(pos+4);
      }
    }
  }

  catch (exception& e)
  {
    cout << e.what();
    throw e;
  }
}
