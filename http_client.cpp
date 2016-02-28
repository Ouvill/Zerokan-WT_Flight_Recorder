//参考

#include "http_client.h"
#include <boost/asio.hpp>
#include <iostream>

using namespace std;
namespace asio = boost::asio;
namespace ip = asio::ip;


Http_Client::Http_Client(std::string url) {
  this->url = url;
  try
  {
    asio::io_service io_service;

    //TCPソケットを作成する
    ip::tcp::socket sock(io_service);

    //名前解決(ホスト名からIPアドレスに変換)する
    ip::tcp::resolver resolver(io_service);
    ip::tcp::resolver::query query(this->url, "http");

    //ホスト情報を設定する
    ip::tcp::endpoint endpoint(*resolver.resolve(query));

    //ソケットへ接続
    sock.connect(endpoint);

    //メッセージを送信
    asio::streambuf request;
    ostream request_ostream(&request);
    request_ostream << "GET /ohmi_bus/tim_dsp.asp?projCd=1&eigCd=2&teicd=3314&KaiKbn=NOW&pole=1 HTTP/1.0\r\n\r\n";
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
      cout << &buffer;
    }

  }
  catch (exception& e)
  {
    cout << e.what();
  }


}
