#include "hudmsg_reader.h"
#include "picojson.hpp"

#include <fstream>
#include <iostream>
#include <sstream>

HudmsgConnector::HudmsgConnector() {
  http_ = new HttpClient("localhost:8111");

}

HudmsgConnector::~HudmsgConnector() {
  delete http_;
}

int HudmsgConnector::get_damages(Damages& damages) {

  std::string get_string;
  std::string json;
  get_string = "/hudmsg?lastEvt=" + std::to_string(lastEvt_) + "&lastDmg=" + std::to_string(lastDmg_);
  try {
    http_->get_data(get_string, json);

    picojson::array damages_json;
    picojson::value v;
    std::ifstream ifs;

//  local_file を 読み込み
//  ifs.open("hudmsg.json");
//  std::istreambuf_iterator<char> it(ifs);
//  std::istreambuf_iterator<char> last;
//  std::string json(it , last);
//  ifs.close();

    get_damages_array(json, damages_json);

//    Damages damages;
    std::vector<ShotDownMsg> shotdown_list;
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
  } catch (std::exception& e){
    throw e;
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


