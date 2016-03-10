#include "hudmsg_reader.h"
#include "picojson.hpp"
#include <fstream>
#include <boost/asio.hpp>
#include <thread>
#include "async_client.h"



HudmsgReader::HudmsgReader() {
  lastEvt_ = 0;
  lastDmg_ = 0;

}

HudmsgReader::~HudmsgReader() {
  delete io_service_;
  delete client_;
}

bool HudmsgReader::connect() {
  io_service_ = new boost::asio::io_service() ;
  client_ = new AsyncClient(*io_service_, "localhost", "8111", "");
  client_->connect();
  io_service_->run();
}


bool HudmsgReader::get_damages(Damages& damages) {

  std::string get_string;
  std::string json;
  get_string = "/hudmsg?lastEvt=" + std::to_string(lastEvt_) + "&lastDmg=" + std::to_string(lastDmg_);

  client_->send(get_string);
  io_service_->run();


  if (!(client_->is_complete())) {
    return false;
  }

  json=client_->body();

  std::cout << json << std::endl;
  picojson::array damages_json;
  picojson::value v;

//    local_file を 読み込み
//  std::ifstream ifs;
//  ifs.open("hudmsg.json");
//  std::istreambuf_iterator<char> it(ifs);
//  std::istreambuf_iterator<char> last;
//  std::string json(it , last);
//  ifs.close();

  get_damages_array(json, damages_json);

//    Damages damages;
  for (picojson::array::iterator i = damages_json.begin(); i != damages_json.end(); ++i) {
    picojson::object damage_object = i->get<picojson::object>();
    Damage damage((int)damage_object["id"].get<double>(), damage_object["msg"].get<std::string>(),
                  damage_object["sender"].get<std::string>(), damage_object["enemy"].get<bool>(),
                  damage_object["mode"].get<std::string>());

    damages.push_back(damage);
    lastDmg_ = (int)damage_object["id"].get<double>();
  }

  return true;
}



int HudmsgReader::get_damages_array(std::string json, picojson::array &damages)
{
  picojson::value v;
  std::string err = parse(v, json);
  if(!err.empty()) {
    std::cerr << picojson::get_last_error() << std::endl;
    return 1;
  }

  picojson::object &o = v.get<picojson::object>();
  damages = o["damage"].get<picojson::array>();

  return 0;
}

void get_data(boost::asio::io_service io_service, AsyncClient client) {

}
