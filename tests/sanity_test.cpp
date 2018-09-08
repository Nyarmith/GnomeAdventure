//test bg and 1 fg obj
#include "../include/GameApp.hpp"

struct BG : public ay::GameObject{
  BG (std::string file) : ay::GameObject(file) {};

  void update(float dt) {};
};

struct Birb : public ay::GameObject{
  Birb (std::string file) : ay::GameObject(file) {

    subscribe(ay::EType::LPRESS,
              [&](auto &e){
      set_pos(rand()%700+20, rand()%700+20);
    });
  };

  void update(float dt) {};
};

int main(){
  BG myBG("assets/Sample_BG.png");
  myBG.set_precedence(0);

  Birb myFG("assets/Sample_Bird.png");
  myFG.set_pos(50,50);
  ay::GameApp &gam = ay::GameApp::instance();

  gam.addObj(&myBG);
  gam.addObj(&myFG);

  gam.run();
}
