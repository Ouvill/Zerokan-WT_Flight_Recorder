#include "mainwindow.h"
#include <QtWidgets>
#include <sstream>
#include "hudmsg_reader.h"
#include "picojson.hpp"
#include <boost/algorithm/string.hpp>
#include <vector>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) , ui(new Ui::MainWindow) {
  setupUi(this);

  Damages damages;
  HudmsgReader hudmsg;
  if(!(hudmsg.get_damages(damages))) {
    std::cout << "error" << std::endl;
  };

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
