#ifndef ZEROKAN_WT_FLIGHT_RECORDER_SETTING_FORM_H
#define ZEROKAN_WT_FLIGHT_RECORDER_SETTING_FORM_H

#include <ui_setting_form.h>
#include <QtWidgets>
#include "ini_accessor.h"

class IniAccessor;


class SettingForm : public QWidget, private Ui::SettingForm{
  Q_OBJECT

private:
  QString user_name;
  IniAccessor *iniAccessor_;

 public:
  SettingForm(QWidget *parent, IniAccessor *iniAccessor);

 public slots:
  void okClicked();
  void applyCliked();

 signals:
  void change_setting();

};


#endif //ZEROKAN_WT_FLIGHT_RECORDER_SETTING_FORM_H
