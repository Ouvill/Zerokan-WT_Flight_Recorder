#include "mainwindow.h"
#include <QtWidgets>
#include <sstream>
#include "hudmsg_reader.h"
#include "picojson.hpp"
#include <boost/algorithm/string.hpp>
#include <vector>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) , ui(new Ui::MainWindow) {
  setupUi(this);

//  std::vector<ShotDownMsg> shotdown_list;
  Damages damages;
  HudmsgReader hudmsg;
  if(!(hudmsg.get_damages(damages))) {
    std::cout << "error" << std::endl;
  };



  std::string dst_msg = "";

  QStringListModel *model = new QStringListModel();
  QStringList qkillList;
  QStringList qkilledList;
  QStringList qdestroyList;
//  for (auto itr = shotdown_list.begin(); itr < shotdown_list.end(); ++itr) {
//    std::string oneline = itr->killer() +"("+itr->killer_airframe()+") -> "
//        + itr->victim() + "(" + itr->victim_airframe() + ")" ;
//    qlist << oneline.c_str();
//  }
  for (auto itr = damages.begin(); itr < damages.end(); ++itr) {
    if(itr->msg().type() == Msg::SHOTDOWN_MSG) {
      ShotDownMsg shotDownMsg(itr->msg());
      killListWidget->addItem(shotDownMsg.killer().c_str());
      killedListWidget->addItem(shotDownMsg.victim().c_str());
    }

    if(itr->msg().type() == Msg::DESTROYED_MSG) {
      DestroyedMsg destroyedMsg(itr->msg());
      destroyListWidget->addItem(destroyedMsg.victim().c_str());
    }
  }
}
