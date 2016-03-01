#include <iostream>
#include "http_client.h"
#include "hudmsg_reader.h"
#include <QApplication>
#include <QTextCodec>
#include "mainwindow.h"

using namespace std;

int main(int argc, char* argv[]) {
    cout << "Hello, World!" << endl;

//  std::string foo;
//  HttpClient *client = new HttpClient("time.khobho.co.jp");
//  client->get_data("/ohmi_bus/tim_dsp.asp?projCd=1&eigCd=2&teicd=3314&KaiKbn=NOW&pole=1",foo);
//  std::cout << foo;

//
//  HudMsgReader hudmsg;
//  hudmsg.get_damages();

  QApplication app(argc, argv);
  QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
  MainWindow *mainWindow = new MainWindow;
  mainWindow->show();
  return app.exec();

}