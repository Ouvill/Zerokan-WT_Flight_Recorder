#include "mainwindow.h"
#include <QtWidgets>
#include <sstream>
#include "hudmsg_reader.h"
#include "picojson.hpp"
#include <boost/algorithm/string.hpp>
#include <vector>

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) , ui(new Ui::MainWindow) {
  setupUi(this);

//  std::vector<ShotDownMsg> shotdown_list;
  Damages damages;
  HudmsgConnector hudmsg;
  hudmsg.get_damages(damages);



  std::string dst_msg = "";

  QStringListModel *model = new QStringListModel();
  QStringList qlist;
//  for (auto itr = shotdown_list.begin(); itr < shotdown_list.end(); ++itr) {
//    std::string oneline = itr->killer() +"("+itr->killer_airframe()+") -> "
//        + itr->victim() + "(" + itr->victim_airframe() + ")" ;
//    qlist << oneline.c_str();
//  }
  for (auto itr = damages.begin(); itr < damages.end(); ++itr) {
    qlist << itr->msg().c_str();
  }

  model->setStringList(qlist);
  listView->setModel(model);

}
