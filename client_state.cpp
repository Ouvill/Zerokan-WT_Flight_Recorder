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

