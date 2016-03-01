#include "game_state.h"
#include "http_client.h"

GameState::GameState() {
  state_=0;
  previous_map_obj="";
}

GameState::~GameState() {
}

int GameState::state() {
  std::string current_map_obj;

  HttpClient http("localhost");
  if (!(http.get_data("/map_obj.json", current_map_obj))) {
    state_ = NotRunnningClient;
    return state_;
  };

  if (previous_map_obj == "" && current_map_obj == "") {
    state_ = NotGaming;
  } else if (previous_map_obj == "" && current_map_obj != "") {
    state_ = GameStart;
  } else if (previous_map_obj != "" && current_map_obj != "") {
    state_ = GameRunning;
  } else if (previous_map_obj != "" && current_map_obj == "") {
    state_ = GameEnd;
  }

  return state_;
}
