#ifndef ZEROKAN_WT_FLIGHT_RECORDER_MAINWINDOW_H
#define ZEROKAN_WT_FLIGHT_RECORDER_MAINWINDOW_H

#include <ui_mainwindow.h>
#include <QtWidgets>

class MainWindow: public QWidget , private Ui::MainWindow {
  Q_OBJECT

 private:
  Ui::MainWindow *ui;

 public:
  MainWindow(QWidget *parent = 0);
};


#endif //ZEROKAN_WT_FLIGHT_RECORDER_MAINWINDOW_H
