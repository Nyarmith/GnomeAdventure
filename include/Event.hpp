#include "common.hpp"
#pragma once

namespace ay{
  enum EType { MMOVE, LPRESS, LRELEASE, RPRESS, RRELEASE}; 
  struct Event{
    EType e;
    int x,y;
  };

  Event txEvt(sf::Event &e){
    Event ret;
    if (e.type == sf::Event::MouseButtonPressed
        && e.mouseButton.button == sf::Mouse::Left){
      ret.e = LPRESS;
      ret.x = e.mouseButton.x;
      ret.y = e.mouseButton.y;

    } else if (e.type == sf::Event::MouseButtonPressed
        && e.mouseButton.button == sf::Mouse::Right){
      ret.e = RPRESS;
      ret.x = e.mouseButton.x;
      ret.y = e.mouseButton.y;

    } else if (e.type == sf::Event::MouseButtonReleased
        && e.mouseButton.button == sf::Mouse::Left){
      ret.e = LRELEASE;
      ret.x = e.mouseButton.x;
      ret.y = e.mouseButton.y;

    } else if (e.type == sf::Event::MouseButtonReleased
        && e.mouseButton.button == sf::Mouse::Left){
      ret.e = RRELEASE;
      ret.x = e.mouseButton.x;
      ret.y = e.mouseButton.y;
    } else if (e.type == sf::Event::MouseMoved){
      ret.e = MMOVE;
      ret.x = e.mouseMove.x;
      ret.y = e.mouseMove.y;
    }

    return ret;
  }

  struct EvtHandler{
    EType type;
    std::function<void(const Event& e)> handle;
    std::function<bool(const Event& e)> filter;
    int precedence;
    bool propagate;
    EvtHandler(EType type,
               std::function<void(const Event& e)> handler,
               std::function<bool(const Event& e)> filter,
               int precedence, bool propagate) :
      type(type), handle(handler), filter(filter),
      precedence(precedence), propagate(propagate)
    {
    }
  };
}
