//test bg and 1 fg obj
#include "../include/GameApp.hpp"

class BG : public ay::GameObject{
  void handle(const ay::Event &e){};
};

class Birb : public ay::GameObject{
  void handle(const ay::Event &e){
    set_pos(rand()%1024, rand()%768);
  };
};

int main(){
  BG myBG;
  Birb myFG;
  ay::GameApp &gam = ay::GameApp::instance();

  myBG.register_sprite("assets/Sample_BG.png",0);
  myFG.register_sprite("assets/Sample_Bird.png",0);
  gam.addObj(&myBG);
  gam.addObj(&myFG);

  gam.run();
}
