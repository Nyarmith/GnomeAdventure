#include "../include/GameApp.hpp"

struct MouseFollower : ay::GameObject {
  bool following{true};
  sf::Vector2f pos_to;
  float vel{1};
  MouseFollower (std::string tex) : ay::GameObject(tex) {
    subscribe(ay::EType::MMOVE, [&](auto &e){
      pos_to.x=e.x;
      pos_to.y=e.y;
    }, [&](auto &e){ return following;});

    subscribe(ay::EType::LPRESS, [&](auto &e){
      randPos();
      following = false;
    }, [&](auto &e){ return (following); }, false);
  }

  void randPos(){
    pos_to.y = rand() % 1000 + 20;
    pos_to.x = rand() % 1000 + 20;
  }


  void update(float dt) override {
    auto cur_pos = get_pos();
    sf::Vector2f nextPos;

    auto dir = pos_to - cur_pos;
    dir = xt::normalize(dir);
    dir = xt::scale(dir,vel*dt);

    nextPos = cur_pos + dir;

    if (!following){
      if (xt::size(pos_to - nextPos) < 20)
        following = true;
    }

    if (!(xt::size(pos_to - nextPos) < 12))
      set_pos(nextPos);
  }
};


int main(){

  MouseFollower ball{"assets/Basketball.png"};
  ball.set_pos(40,40);


  ay::GameApp &ga = ay::GameApp::instance();

  ga.addObj(&ball);
  ga.run();
}
