//test bg and 1 fg obj
#include "../include/GameApp.hpp"

struct BG : public ay::GameObject{
  BG (std::string file) : ay::GameObject(file) { };
  void handle(const ay::Event &e){};
  void update(float dt) {};
};

struct Birb : public ay::GameObject{
  Birb (std::string file) : ay::GameObject(file) { };
  void handle(const ay::Event &e){
    //set_pos(rand()%1024, rand()%768);
  };
  void update(float dt) {};
};

int main(){
  BG myBG("assets/Sample_BG.png");
  myBG.set_precedence(0);
  myBG.set_pos(20,20);

  Birb myFG("assets/Sample_Bird.png");
  myFG.set_pos(50,50);
  ay::GameApp &gam = ay::GameApp::instance();

  gam.addObj(&myBG);
  gam.addObj(&myFG);

  gam.run();
}
