#ifndef ZEROKAN_WT_FLIGHT_RECORDER_MAINWINDOW_H
#define ZEROKAN_WT_FLIGHT_RECORDER_MAINWINDOW_H

#include <ui_mainwindow.h>
#include <QtWidgets>

class User;
class GameState;
class Damages;
class HudmsgReader;

class MainWindow: public QMainWindow , private Ui::MainWindow {
  Q_OBJECT

 private:
  Ui::MainWindow *ui;
  User *user;
  GameState *game_state;
  Damages *damages;
  HudmsgReader *hudmsg;

  int myTimerId;

 public:
  MainWindow(QWidget *parent = 0);
  ~MainWindow();

 protected:
  void timerEvent(QTimerEvent *e);

 private slots:
  void createUser();


};


#endif //ZEROKAN_WT_FLIGHT_RECORDER_MAINWINDOW_H
