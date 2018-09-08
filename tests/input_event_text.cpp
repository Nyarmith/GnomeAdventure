#include "../include/GameApp.hpp"

struct MouseFollower : ay::GameObject {
  bool following{true};
  float x{100},y{100};
  float vel{100};
  MouseFollower (std::string tex) : ay::GameObject(tex) {
  }

  void randPos(){
    y = rand() % 1000 + 20;
    x = rand() % 1000 + 20;
  }
  void handle(const ay::Event &e) override {
    switch(e.e){
      case ay::LPRESS:
        randPos();
        following=false;
        break;
      case ay::MMOVE:
        x = e.x;
        y = e.y;
    }
  }

  void update(float dt) override {
    auto cur_pos = get_pos();
    float next_x, next_y;

    auto dir = sf::Vector2f{x,y} - cur_pos;
    dir = xt::normalize(dir);
    dir = xt::scale(dir,vel*dt);
    next_x = dir.x + cur_pos.x;
    next_y = dir.y + cur_pos.y;
    if (!following){
      if (xt::size(sf::Vector2f{x,y} - cur_pos) < 20)
        following = false;
    }
    set_pos(next_x, next_y);
  }
};


int main(){

  MouseFollower ball{"assets/Basketball.png"};
  ball.set_pos(40,40);


  ay::GameApp &ga = ay::GameApp::instance();

  ga.addObj(&ball);
  ga.run();
}
