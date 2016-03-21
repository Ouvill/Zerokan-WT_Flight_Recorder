#include "game_state.h"
#include "async_client.h"
#include <boost/asio.hpp>

GameState::GameState() {
  state_=0;
  previous_map_obj="";
//
//  io_service_ = new boost::asio::io_service();
//  client_ = new AsyncClient(*io_service_, "localhost" , "8111", "/map_obj.json");
//  client_->connect();
//  io_service_->run();
}

GameState::~GameState() {
}

int GameState::get() {
  std::string current_map_obj;

  io_service_ = new boost::asio::io_service();
  client_ = new AsyncClient(*io_service_, "localhost" , "8111", "/map_obj.json");
  client_->connect();
  io_service_->run();

  client_->send();
  io_service_->run();

  if (!(client_->is_complete())) {
    state_ = NotRunnningClient;
    return state_;
  };

  current_map_obj = client_->body();

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
