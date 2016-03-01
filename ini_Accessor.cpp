#include "ini_Accessor.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/optional.hpp>

using namespace boost::property_tree;

IniReader::IniReader(std::string filename) {
  ptree pt;
  read_ini(":/data/setting.ini",pt);

  if (boost::optional<std::string> user_name_option = pt.get_optional<std::string>("Data.user_name")) {
    user_name_ = user_name_option.get();
  } else {
    user_name_ = "no_name_";
  }

  if (boost::optional<std::string> client_path_option = pt.get_optional<std::string>("Data.warthunder_client_path")) {
    warthunder_client_path_ = client_path_option.get();
  } else {
    warthunder_client_path_ = 'C:\Program Files (x86)\Steam\steamapps\common\War Thunder\launcher.exe';
  }

}
