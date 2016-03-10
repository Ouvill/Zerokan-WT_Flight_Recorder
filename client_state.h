#ifndef ZEROKAN_WT_FLIGHT_RECORDER_CLIENT_STATE_H
#define ZEROKAN_WT_FLIGHT_RECORDER_CLIENT_STATE_H
#include <QObject>

class ClientState: public QObject {
  Q_OBJECT
 private:
  QString process_;
 public:
  ClientState(QString process);
  bool isRunning();

};


#endif //ZEROKAN_WT_FLIGHT_RECORDER_CLIENT_STATE_H
