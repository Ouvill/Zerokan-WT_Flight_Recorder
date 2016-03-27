#include "mainwindow.h"
#include "setting_form.h"
#include <sstream>
#include <boost/algorithm/string.hpp>
#include <QtCore/qstring.h>
#include "hudmsg_reader.h"
#include "ini_accessor.h"
#include "game_state.h"
#include "user.h"
#include "timer.h"
#include <fstream>
#include <boost/filesystem/operations.hpp>

static const int LOOP_TIME = 5000;
static const std::string RECORDS_FILE = "./data/records.csv";
static const std::string REVANGE_LIST = "./data/revange_list.csv";

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) , ui(new Ui::MainWindow) {
  setupUi(this);

  ini_ = new IniAccessor("./data/setting.ini");
  user_ = new User(ini_->user_name());
  playerNameLabel->setText(user_->name().c_str());

  game_state_ = new GameState();
  damages_ = new Damages();
  hudmsg_ = new HudmsgReader();
  myTimerId = startTimer(LOOP_TIME);


  connect(settingAction, SIGNAL(triggered()), this, SLOT(settingSelected()));

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
        // kill
        if (shotDownMsg.killer().find(user_->name()) != std::string::npos) {
          std::string killMsg = shotDownMsg.victim() + "(" + shotDownMsg.victim_airframe() + ")";
          killListWidget->addItem(killMsg.c_str());
          user_->record()->add_kill_count();
        }

        // killed by
        if (shotDownMsg.victim().find(user_->name()) != std::string::npos) {
          std::string killedByMsg = shotDownMsg.killer() + "(" + shotDownMsg.killer_airframe() + (")");
          killedByListWidget->addItem(killedByMsg.c_str());
          user_->record()->add_death_count();

          if (!boost::filesystem::exists(REVANGE_LIST)) {
            std::ofstream of(REVANGE_LIST, std::ios::app);

            of << "戦闘開始時刻,敵プレイヤー名,敵の機体,自身の機体" << std::endl;
            of.close();
          }

          time_t time = timer_->start_time();
          struct tm *tm_st = localtime(&time);
          std::ofstream of(REVANGE_LIST, std::ios::app);
          of << tm_st->tm_year << tm_st->tm_mon+1 << tm_st->tm_mday << "_" << tm_st->tm_hour << tm_st->tm_min << tm_st->tm_sec << ",";
          of << shotDownMsg.killer() << ",";
          of << shotDownMsg.killer_airframe() << ",";
          of << shotDownMsg.victim_airframe() << std::endl;
          of.close();

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

void MainWindow::settingSelected() {
  settingForm_ = new SettingForm(0, ini_);
  settingForm_->show();

  connect(settingForm_, SIGNAL(change_setting()), this, SLOT(relord_setting()));
}


void MainWindow::relord_setting() {
  delete user_;
  user_ = new User(ini_->user_name());
  playerNameLabel->setText(user_->name().c_str());
}

void MainWindow::update_result_widget() {
  double kill_ratio = user_->record()->kill_ratio();
  killDeathLabel->setText(QString::number(kill_ratio));


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
        hudmsg_->get_damages(*damages_);
        break;

      case GameState::GameStart:
        clientStateLabel->setText(tr("running"));
        gameStateLabel->setText(tr("start"));
        user_->reset_record();
        timer_ = new Timer();
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
        timer_->stop();
        user_->record()->export_csv(RECORDS_FILE,timer_->start_time());


        clientStateLabel->setText(tr("running"));
        gameStateLabel->setText(tr("end"));

        break;

    }
  }
}


