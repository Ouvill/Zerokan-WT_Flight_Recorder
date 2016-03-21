#ifndef ZEROKAN_WT_FLIGHT_RECORDER_MAINWINDOW_H
#define ZEROKAN_WT_FLIGHT_RECORDER_MAINWINDOW_H

#include <ui_mainwindow.h>
#include <QtWidgets>
#include "damages.h"

class User;
class GameState;
class HudmsgReader;
class ClientState;

class MainWindow: public QMainWindow , private Ui::MainWindow {
  Q_OBJECT

 private:
  Ui::MainWindow *ui;
  User *user_;
  ClientState *client_state_;
  GameState *game_state_;
  Damages *damages_;
  HudmsgReader *hudmsg_;

  int clientRunningTimer;
  int isClientRunnningTimer;

  void list_clear();
  void update_result_widget();
  void serch_user_msg();
  void onRunningClient();

 public:
  MainWindow(QWidget *parent = 0);
  ~MainWindow();

 protected:
  void timerEvent(QTimerEvent *e);




};


#endif //ZEROKAN_WT_FLIGHT_RECORDER_MAINWINDOW_H
