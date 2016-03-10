#ifndef ZEROKAN_WT_FLIGHT_RECORDER_CLIENT_STATE_H
#define ZEROKAN_WT_FLIGHT_RECORDER_CLIENT_STATE_H
#include <QObject>

class ClientState: public QObject {
  Q_OBJECT
 private:
  bool state_ = false;
  bool previous_state=false;
  QString process_;
 public:
  enum {
    NOT_RUNNING = -1,
    START = 0,
    RUNNING = 1,
    END = 2,
  };

  ClientState(QString process);
  int get();
  bool isRunning();

};


#endif //ZEROKAN_WT_FLIGHT_RECORDER_CLIENT_STATE_H
