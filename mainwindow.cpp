#include "mainwindow.h"
#include <sstream>
#include <boost/algorithm/string.hpp>
#include <QtCore/qstring.h>
#include "hudmsg_reader.h"
#include "ini_accessor.h"
#include "game_state.h"
#include "user.h"
#include "timer.h"
#include "client_state.h"


static const int CHECK_TIME = 500;
static const int LOOP_TIME = 5000;


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) , ui(new Ui::MainWindow) {
  setupUi(this);

  IniAccessor ini("./data/setting.ini");
  user_ = new User(ini.user_name());
  playerNameLabel->setText(user_->name().c_str());

  game_state_ = new GameState();
  damages_ = new Damages();
  hudmsg_ = new HudmsgReader();
  client_state_ = new ClientState("aces.exe");

  isClientRunnningTimer = startTimer(CHECK_TIME);


}


MainWindow::~MainWindow() {
  delete user_;
  delete game_state_;
}

void MainWindow::list_clear() {
  killListWidget->clear();
  killedByListWidget->clear();
  destroyListWidget->clear();
}

void MainWindow::serch_user_msg() {
  Damages *tmp_damages = new Damages;
  hudmsg_->get_damages(*tmp_damages);

  for (auto itr = tmp_damages->begin(); itr != tmp_damages->end(); ++itr) {

    switch ( itr->msg().type()) {
      case  Msg::SHOTDOWN_MSG : {
        ShotDownMsg shotDownMsg(itr->msg());
        if (shotDownMsg.killer().find(user_->name()) != std::string::npos) {
          std::string killMsg = shotDownMsg.victim() + "(" + shotDownMsg.victim_airframe() + ")";
          killListWidget->addItem(killMsg.c_str());
          user_->record()->add_kill_count();
        }

        if (shotDownMsg.victim().find(user_->name()) != std::string::npos) {
          std::string killedByMsg = shotDownMsg.killer() + "(" + shotDownMsg.killer_airframe() + (")");
          killedByListWidget->addItem(killedByMsg.c_str());
          user_->record()->add_death_count();
        }
        break;
      }

      case Msg::DESTROYED_MSG : {
        DestroyedMsg destroyedMsg(itr->msg());
        if (destroyedMsg.killer().find(user_->name()) != std::string::npos) {
          destroyListWidget->addItem(destroyedMsg.victim().c_str());
          user_->record()->add_destroy_count();
        }

        break;
      }

      case Msg::CRASHED_MSG : {
        DamageMsg crashedMsg(itr->msg());
        if (crashedMsg.killer().find(user_->name()) != std::string::npos) {
          killedByListWidget->addItem("You are crash");
          user_->record()->add_death_count();
        }

        break;
      }
    }
  }

  damages_->splice(damages_->end(), *tmp_damages);
  delete tmp_damages;

}

void MainWindow::update_result_widget() {
  double kill_ratio = user_->record()->kill_ratio();
  killDeathLabel->setText(QString::number(kill_ratio));


}

// ループ処理
void MainWindow::timerEvent(QTimerEvent *e) {
  if (e->timerId() == isClientRunnningTimer) {
    //TODO タスクマネージャーからaces.exe が起動しているかチェック
    switch (client_state_->get()) {
      case ClientState::NOT_RUNNING:

        break;

      case ClientState::START:

        hudmsg_ = new HudmsgReader();
        game_state_ = new GameState();

        std::cout << "Start" << std::endl;

        break;

      case ClientState::RUNNING:
        onRunningClient();

        std::cout << "RUNNNING" << std::endl;
        break;

      case ClientState::END:
        std::cout << "END" << std::endl;
        break;
    }
  }

//  if (e->timerId() == clientRunningTimer) {
//    std::cout << "loop" << endl;
//    onRunningClient();
//
//  }
}

void MainWindow::onRunningClient() {
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
      hudmsg_->connect();
      list_clear();


      delete damages_;
      damages_ = new Damages();
      std::cout << "game start" << std::endl;

      break;

    case GameState::GameRunning:
      clientStateLabel->setText(tr("running"));
      gameStateLabel->setText(tr("running"));
      serch_user_msg();
      update_result_widget();
      break;

    case GameState::GameEnd:
      serch_user_msg();


      clientStateLabel->setText(tr("running"));
      gameStateLabel->setText(tr("end"));

      break;

  }
}
