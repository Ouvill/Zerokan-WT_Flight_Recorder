#include "mainwindow.h"
#include <QtWidgets>
#include <sstream>
#include "hudmsg_reader.h"
#include "picojson.hpp"
#include <boost/algorithm/string.hpp>
#include <vector>

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
  setupUi(this);

  QTextCodec* tc = QTextCodec::codecForLocale();

  picojson::array damages;
  HudmsgConnector hudmsg;
  hudmsg.get_damages(damages);


  std::string oneline;
  std::string dst_msg = "";
  for (picojson::array::iterator i = damages.begin(); i != damages.end(); ++i) {
    picojson::object damage = i->get<picojson::object>();

    std::string damage_msg = damage["msg"].get<std::string>();

    std::vector<std::string> vector;
    boost::split(vector, damage_msg, boost::is_space());

    std::string player = vector[0];
//    std::string airforce = vector[1];

    dst_msg += player + ":" + "\n";
   }

  QString qStr = QString(tc->toUnicode(dst_msg.c_str()));
  label->setText(qStr);

}
