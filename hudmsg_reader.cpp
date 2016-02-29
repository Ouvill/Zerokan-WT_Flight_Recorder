#include "hudmsg_reader.h"
#include "picojson.hpp"

#include <fstream>
#include <iostream>
#include <sstream>

HudmsgConnector::HudmsgConnector() {
//  http = new HttpClient("localhost:8111");

}

HudmsgConnector::~HudmsgConnector() {
//  delete http;
}

int HudmsgConnector::get_damages(std::vector<ShotDownMsg>& shotdown_list) {

//  std::string get_string;
//  std::string json;
//  get_string = "/hudmsg?lastEvt=" + std::to_string(lastEvt_) + "&lastDmg=" + std::to_string(lastDmg_);
//  http->get_data(get_string, json);

  picojson::array damages_json;
  picojson::value v;
  std::ifstream ifs;

  //local_file を 読み込み
  ifs.open("hudmsg.json");
  std::istreambuf_iterator<char> it(ifs);
  std::istreambuf_iterator<char> last;
  std::string json(it , last);
  ifs.close();

  get_damages_array(json, damages_json);

  Damages damages;
  std::vector<ShotDownMsg> shot_down_msgs;
  std::vector<DestroyedMsg> destroyed_msgs;

  for (picojson::array::iterator i = damages_json.begin(); i != damages_json.end(); ++i) {
    picojson::object damage_object = i->get<picojson::object>();
    Damage damage((int)damage_object["id"].get<double>(), damage_object["msg"].get<std::string>(),
           damage_object["sender"].get<std::string>(), damage_object["enemy"].get<bool>(),
           damage_object["mode"].get<std::string>());

    if(damage.msg().isShotDownMsg()) {
      shotdown_list.push_back(ShotDownMsg(damage.msg()));
    }

    if(damage.msg().isDestoryedMsg()) {
      destroyed_msgs.push_back(DestroyedMsg(damage.msg()));
    }

    damages.push_back(damage);
    lastDmg_ = (int)damage_object["id"].get<double>();
  }
}

int HudmsgConnector::get_damages_array(std::string json, picojson::array &damages)
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

Msg::Msg(std::string msg):std::string(msg) {};

bool Msg::isShotDownMsg() {
  if (find(" shot down ") != std::string::npos) { return true;}
  else {return false;};
}

bool Msg::isDestoryedMsg() {
  if (find(" destroyed ") != std::string::npos ) {
    return true;
  } else { return false;};
}



//std::string msg の データ
//=ECVAS= DK_DaiZi_CN (スピットファイア F) shot down =BAT= masterchieffffff (ウェリントン)
//Jokebo (IL-10) destroyed 駆逐艦"
Damage::Damage(int id, std::string msg, std::string sender, bool enemy, std::string mode) : msg_(msg) {
  this->id_ = id;
  this->sender_ = sender;
  this->eneny_ = enemy;
  this->mode_ = mode;
}

Msg Damage::msg() { return msg_;};

void Damages::serch_shot_down() {

}

DamageMsg::DamageMsg(const std::string& msg) {
  std::size_t open_quote_pos = msg.find("(");
  killer_ = std::string(msg, 0, open_quote_pos -1);
  std::size_t close_quote_pos = msg.find(")");
  killer_airframe_ = std::string(msg, open_quote_pos + 1, close_quote_pos - open_quote_pos -1);
}

std::string DamageMsg::killer() {return killer_;}
std::string DamageMsg::killer_airframe() {return killer_airframe_; }

ShotDownMsg::ShotDownMsg(const std::string& msg) : DamageMsg(msg) {
  std::string keyword = " shot down ";

  std::size_t keyword_pos = msg.find(keyword);
  std::size_t after_keyword_pos = keyword_pos + keyword.length();

  std::size_t secound_open_quote = msg.find("(", after_keyword_pos);
  victim_ = std::string(msg, after_keyword_pos, secound_open_quote - after_keyword_pos -1) ;
  std::size_t secound_close_quote = msg.find(")", after_keyword_pos);
  victim_airframe_ = std::string(msg, secound_open_quote + 1, secound_close_quote - secound_open_quote -1);

}

std::string ShotDownMsg::victim() {
  return victim_;
}

std::string ShotDownMsg::victim_airframe() {
  return victim_airframe_;
}

//std::string msg のデータ
//Jokebo (IL-10) destroyed 駆逐艦"
DestroyedMsg::DestroyedMsg(const std::string& msg) : DamageMsg(msg) {
  std::string keyword = " destroyed ";
  std::size_t keyword_pos = msg.find(keyword);
  std::size_t after_keyword_pos = keyword_pos + keyword.length();
  victim_ = std::string(msg, after_keyword_pos);
}

std::string DestroyedMsg::victim() {
  return victim_;
}
