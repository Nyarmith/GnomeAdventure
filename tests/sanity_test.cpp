//test bg and 1 fg obj
#include "../include/GameApp.hpp"

struct BG : public ay::GameObject{
  BG (std::string file, sf::IntRect dim) : ay::GameObject(file, dim) { };
  void handle(const ay::Event &e){};
};

struct Birb : public ay::GameObject{
  Birb (std::string file, sf::IntRect dim) : ay::GameObject(file, dim) { };
  void handle(const ay::Event &e){
    set_pos(rand()%1024, rand()%768);
  };
};

int main(){
  BG myBG("assets/Sample_BG.png", sf::IntRect(0,0,1024,768));
  Birb myFG("assets/Sample_Bird.png", sf::IntRect(150,50,400,400));
  ay::GameApp &gam = ay::GameApp::instance();

  gam.addObj(&myBG);
  gam.addObj(&myFG);

  gam.run();
}
