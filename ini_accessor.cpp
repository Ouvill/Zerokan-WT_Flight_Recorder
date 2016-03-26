#include "ini_accessor.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/optional.hpp>

using namespace boost::property_tree;

IniAccessor::IniAccessor(const std::string& filename) {
  filename_ = filename;

  ptree pt;
  read_ini(filename_,pt);

  if (boost::optional<std::string> user_name_option = pt.get_optional<std::string>("Data.user_name")) {
    user_name_ = user_name_option.get();
  } else {
    user_name_ = "no_name_";
  }

  if (boost::optional<std::string> client_path_option = pt.get_optional<std::string>("Data.warthunder_client_path")) {
    warthunder_client_path_ = client_path_option.get();
  } else {
    warthunder_client_path_ = "C:\\Program Files (x86)\\Steam\\steamapps\\common\\War Thunder\\launcher.exe";
  }

}
std::string IniAccessor::user_name() {
  return user_name_;
}

std::string IniAccessor::warthunder_client_path() {
  return warthunder_client_path_;
}

void IniAccessor::set_user_name(std::string user_name) {
  user_name_ = user_name;
}


void IniAccessor::export_ini() {
  ptree pt;

  pt.put("Data.user_name",user_name_ );
  pt.put("Data.warthunder_client_path", warthunder_client_path_);

  write_ini(filename_, pt);
}

