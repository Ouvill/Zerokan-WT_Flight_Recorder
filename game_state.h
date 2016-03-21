

#ifndef ZEROKAN_WT_FLIGHT_RECORDER_GAME_STATE_H
#define ZEROKAN_WT_FLIGHT_RECORDER_GAME_STATE_H
#include <string>

namespace boost {
namespace asio {
class io_service;
};
};

class AsyncClient;


class GameState {
 private:
  int state_;
  std::string previous_map_obj;

  boost::asio::io_service *io_service_;
  AsyncClient *client_;

 public:
  enum {
    NotRunnningClient = -1,
    NotGaming = 0,
    GameStart = 1,
    GameRunning = 2,
    GameEnd = 3
  };

  GameState();
  ~GameState();
  int get();
};


#endif //ZEROKAN_WT_FLIGHT_RECORDER_GAME_STATE_H
