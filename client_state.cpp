#include <QtCore>

#include "client_state.h"
ClientState::ClientState(QString process) {
  process_ = process;
}

bool ClientState::isRunning() {
  QProcess tasklist;
  tasklist.start(
      "tasklist",
      QStringList() << "/NH"
          << "/FO" << "CSV"
          << "/FI" << QString("IMAGENAME eq %1").arg(process_));
  tasklist.waitForFinished();
  QString output = tasklist.readAllStandardOutput();
  return output.startsWith(QString("\"%1").arg(process_));
}

int ClientState::get(){
  int state;
  state_ = isRunning();
  if (!previous_state_ && !state_) {
    state = NOT_RUNNING;
  } else if (!previous_state_ && state_) {
    state = START;
  } else if (previous_state_ && state_) {
    state = RUNNING;
  } else if (previous_state_ && !state_) {
    state = END;
  }

  previous_state_ = state_;
  return state;

}