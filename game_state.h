

#ifndef ZEROKAN_WT_FLIGHT_RECORDER_GAME_STATE_H
#define ZEROKAN_WT_FLIGHT_RECORDER_GAME_STATE_H
#include <string>

class GameState {
  private:
    int state_;
    std::string previous_map_obj;

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
  int state();
};


#endif //ZEROKAN_WT_FLIGHT_RECORDER_GAME_STATE_H
