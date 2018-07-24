#include "common.hpp"
#include "Event.hpp"

class GameObject{
  public:
    GameObject(string texture, sf::Vector2i dimension, sf::Vector2i pos, float rot);
    virtual bool draw(int frameNum);
    virtual bool handle(Event e);

  protected:
    int fnum_;  //"public" current frame
    sf::Vector2i pos_;
    sf::Vector2i dim_; //dimensions for an individual sprite
    float rot_;
    sf::Texture tex_;


  //private interface used by GameApp
  private:
    int cframe_;  //actual current frame
    void refresh();
};



void GameObject::refresh(){
}
