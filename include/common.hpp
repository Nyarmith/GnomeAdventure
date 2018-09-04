#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <algorithm>
#include <cstdint>
#include <thread>
#include <mutex>
#include <string>
#include <stack>
#include <queue>
#include <chrono>
#include <sstream>
#include <atomic>
#include <cmath>
#include <condition_variable>
#include <functional>
#include <exception>
#include <unordered_map>
#include "trace.hpp"

using std::string;
using std::vector;

namespace xt{
  void usleep(long long t){
    std::this_thread::sleep_for(std::chrono::milliseconds(t));
  }

  //some simple vec utils
  template<typename T>
  float size(T in){
    float ret = std::sqrt(in.x*in.x + in.y*in.y);
    return ret;
  }
  template<typename T>
  T normalize(T in){
    float div = std::sqrt(in.x*in.x + in.y*in.y);
    T ret{in.x/div, in.y/div};
    return ret;
  }

  template<typename T>
  T scale(T in, float c){
    T ret{in.x*c, in.y*c};
    return ret;
  }
}
