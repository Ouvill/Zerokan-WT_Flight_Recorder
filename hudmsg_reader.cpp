#include "hudmsg_reader.h"
#include "picojson.hpp"

#include <fstream>
#include <iostream>
#include <sstream>

HudmsgReader::HudmsgReader() {
//  http = new HttpClient("localhost:8111");

}

HudmsgReader::~HudmsgReader() {
//  delete http;
}

int HudmsgReader::get_msg() {

  std::cout << "test" << std::endl;
//  std::string get_string;
//  std::string json;
//  get_string = "/hudmsg?lastEvt" + std::to_string(lastEvt) + "&lastDmg" = std::to_string(lastDmg);
//  http->get_data(get_string, json);

  picojson::value v;
  std::ifstream infile;
  std::string json="";

  infile.open("hudmsg.json");
  while(!infile.eof()) {
    std::string work="";
    infile >> work;
    json += work;
  }

  infile.close();



  picojson::array damages;
  get_damages_array(json, damages);
  for (picojson::array::iterator i = damages.begin(); i != damages.end(); ++i) {
    picojson::object damage = i->get<picojson::object>();
    std::cout << damage["id"].get<double>() << ":" << damage["msg"].get<std::string>() << std::endl;
  }


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
