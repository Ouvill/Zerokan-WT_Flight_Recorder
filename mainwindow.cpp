#include "mainwindow.h"
#include <sstream>
#include <boost/algorithm/string.hpp>
#include "hudmsg_reader.h"
#include "ini_accessor.h"
#include "game_state.h"
#include "user.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) , ui(new Ui::MainWindow) {
  setupUi(this);

  IniAccessor ini("../data/setting.ini");
  user = new User(ini.user_name());

  game_state = new GameState();
  damages = new Damages();
  myTimerId = startTimer(1000);

  connect(applyUserNameButton, SIGNAL(clicked()), this, SLOT(createUser()));

}


MainWindow::~MainWindow() {
  delete user;
  delete game_state;
}

void MainWindow::createUser() {
  delete user;
  user = new User(userNameLineEdit->text().toStdString());
}


// ループ処理
void MainWindow::timerEvent(QTimerEvent *e) {
  if (e->timerId() == myTimerId) {
    switch (game_state->get() ) {
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
        user->reset_record();

        killListWidget->clear();
        killedListWidget->clear();
        destroyListWidget->clear();

        delete damages;
        damages = new Damages();

        break;

      case GameState::GameRunning:
        clientStateLabel->setText(tr("running"));
        gameStateLabel->setText(tr("running"));

        hudmsg->get_damages(*damages);
        for (auto itr = damages->begin(); itr < damages->end(); ++itr) {
//          if ( itr->msg().find(user->name()) != std::string::npos) {
            if (itr->msg().type() == Msg::SHOTDOWN_MSG) {
              ShotDownMsg shotDownMsg(itr->msg());
              killListWidget->addItem(shotDownMsg.killer().c_str());
              killedListWidget->addItem(shotDownMsg.victim().c_str());
            }

            if (itr->msg().type() == Msg::DESTROYED_MSG) {
              DestroyedMsg destroyedMsg(itr->msg());
              destroyListWidget->addItem(destroyedMsg.victim().c_str());
            }
//          }
        }
        break;

      case GameState::GameEnd:
        clientStateLabel->setText(tr("running"));
        gameStateLabel->setText(tr("end"));
        break;

    }
  }
}


