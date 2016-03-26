#include "setting_form.h"
#include "ini_accessor.h"

SettingForm::SettingForm(QWidget *parent , IniAccessor *iniAccessor ) : QWidget(parent) , iniAccessor_(iniAccessor){
  setupUi(this);

  connect(okButton, SIGNAL(clicked()), this, SLOT(okClicked()));
  connect(applyButton, SIGNAL(clicked()), this, SLOT(applyCliked()));
  connect(cancelButton, SIGNAL(clicked()), this, SLOT(close()));

}


void SettingForm::okClicked() {
  applyCliked();
  close();
}

void SettingForm::applyCliked() {
  iniAccessor_->set_user_name(userNameLineEdit->text().toStdString());
  iniAccessor_->export_ini();

  change_setting();
}
