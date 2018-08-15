#include "../include/common.hpp"


int main(){
  sf::RenderWindow win(sf::VideoMode(1024,768), "HomeAdventure");
  sf::Texture bg;
  sf::Texture fg;
  bg.loadFromFile("assets/Sample_BG.png");
  fg.loadFromFile("assets/Sample_Bird.png");

  sf::Sprite a;
  sf::Sprite b;
  a.setTexture(bg);
  b.setTexture(fg);

  win.draw(a);
  win.draw(b);

  win.display();

  xt::usleep(300000);
}
