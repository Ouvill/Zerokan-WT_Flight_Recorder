#include "game_state.h"
#include "async_client.h"
#include <boost/asio>

GameState::GameState() {
  state_=0;
  previous_map_obj="";
}

GameState::~GameState() {
}

int GameState::get() {
  std::string current_map_obj;

  boost::asio::io_service io_service;
  AsyncClient client(io_service, "localhost" , "8111", "/map_obj.json");
  io_service.run();

  if (!(client.is_complete)) {
    state_ = NotRunnningClient;
    return state_;
  };

  current_map_obj = client.body();

  if (previous_map_obj == "" && current_map_obj == "") {
    state_ = NotGaming;
  } else if (previous_map_obj == "" && current_map_obj != "") {
    state_ = GameStart;
  } else if (previous_map_obj != "" && current_map_obj != "") {
    state_ = GameRunning;
  } else if (previous_map_obj != "" && current_map_obj == "") {
    state_ = GameEnd;
  }

  previous_map_obj = current_map_obj;
  return state_;
}
