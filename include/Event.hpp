#include "common.hpp"

namespace ay{
  enum EType { MMOVE, LPRESS, LRELEASE, RPRESS, RRELEASE}; 
  struct Event{
    EType e;
    int x,y;
  };

  Event txEvt(sf::Event &e){
    Event ret;
    if        (e.type == sf::Event::MouseButtonPressed
        && e.mouseButton.button == sf::Mouse::Left){
      ret.e = LPRESS;

    } else if (e.type == sf::Event::MouseButtonPressed
        && e.mouseButton.button == sf::Mouse::Right){
      ret.e = RPRESS;

    } else if (e.type == sf::Event::MouseButtonReleased
        && e.mouseButton.button == sf::Mouse::Left){
      ret.e = LRELEASE;

    } else if (e.type == sf::Event::MouseButtonReleased
        && e.mouseButton.button == sf::Mouse::Left){
      ret.e = RRELEASE;
    } else {
      ret.e = MMOVE;
    }

    return ret;
  }
}
