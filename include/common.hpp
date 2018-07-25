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
#include <atomic>
#include <condition_variable>

using std::string;
using std::vector;

namespace xt{
  void usleep(long long t){
    std::this_thread::sleep_for(std::chrono::milliseconds(t));
  }

}
