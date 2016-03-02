#include "mainwindow.h"
#include <sstream>
#include <boost/algorithm/string.hpp>
#include <QtCore/qstring.h>
#include "hudmsg_reader.h"
#include "ini_accessor.h"
#include "game_state.h"
#include "user.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) , ui(new Ui::MainWindow) {
  setupUi(this);

  IniAccessor ini("../data/setting.ini");
  user_ = new User(ini.user_name());
  playerNameLabel->setText(user_->name().c_str());

  game_state_ = new GameState();
  damages_ = new Damages();
  myTimerId = startTimer(2000);

}


MainWindow::~MainWindow() {
  delete user_;
  delete game_state_;
}

void MainWindow::list_clear() {
  killListWidget->clear();
  killedListWidget->clear();
  destroyListWidget->clear();
}

void MainWindow::serch_user_msg() {
  Damages *tmp_damages = new Damages;
  hudmsg->get_damages(*tmp_damages);

  for (auto itr = tmp_damages->begin(); itr != tmp_damages->end(); ++itr) {
    if ( itr->msg().find(user_->name()) != std::string::npos) {
      if (itr->msg().type() == Msg::SHOTDOWN_MSG) {
        ShotDownMsg shotDownMsg(itr->msg());
        killListWidget->addItem(shotDownMsg.killer().c_str());
        killedListWidget->addItem(shotDownMsg.victim().c_str());
      }

      if (itr->msg().type() == Msg::DESTROYED_MSG) {
        DestroyedMsg destroyedMsg(itr->msg());
        destroyListWidget->addItem(destroyedMsg.victim().c_str());
      }
    }
  }

  damages_->splice(damages_->end(), *tmp_damages);
  delete tmp_damages;

}


// ループ処理
void MainWindow::timerEvent(QTimerEvent *e) {
  if (e->timerId() == myTimerId) {
    switch (game_state_->get() ) {
      case GameState::NotRunnningClient:
        clientStateLabel->setText(tr("not running"));
        gameStateLabel->setText(tr("not running"));
        break;

      case GameState::NotGaming:
        clientStateLabel->setText(tr("running"));
        gameStateLabel->setText(tr("not running"));

        break;

      case GameState::GameStart:
        clientStateLabel->setText(tr("running"));
        gameStateLabel->setText(tr("start"));
        user_->reset_record();
        list_clear();


        delete damages_;
        damages_ = new Damages();

        std::cout << "game start" << std::endl;

        break;

      case GameState::GameRunning:
        clientStateLabel->setText(tr("running"));
        gameStateLabel->setText(tr("running"));

        serch_user_msg();
        break;

      case GameState::GameEnd:
        clientStateLabel->setText(tr("running"));
        gameStateLabel->setText(tr("end"));
        break;

    }
  }
}

