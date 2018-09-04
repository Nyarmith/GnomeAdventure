#include "GUIObject.hpp"
#include "AudioStore.hpp"

const long long DELAY = 25;
const long long RESX  = 1024;
const long long RESY  = 768;

namespace ay{
  class GameApp{
    public:
      /**
       * instance()
       * Gets instance of the game being run
       */
      static GameApp& instance(){
        if (!GameApp_instance_)
          GameApp_instance_ = new GameApp;
        return *GameApp_instance_;
      }

      /**
       * run()
       * runs the GameApp given its setup entities
       */
      void run(){
        win_.create(sf::VideoMode(RESX, RESY), "GnomeAdventure");

        //LOG_DEBUG("Created window");

        sf::Clock timer;
        while(gameRunning_){
          float dt = timer.getElapsedTime().asSeconds();
          poll();
          update(dt);
          draw();
          //xt::usleep( DELAY - dt );
        }
        win_.close();
      }

      /**
       * exit()
       * safely ends the application
       */
      void exit(){
        gameRunning_ = false;
      }

      void addObj(GameObject *o){ gameObjs_.push_back(o); }

      void subscribe_event(const EType evt_type,
                           std::function<void(const Event &e)> handler,
                           std::function<bool(const Event&e)> filter = [](auto in){return true;},
                           int precedence=0,
                           bool propagate_evt=true){
        EvtHandlers_.push_back( EvtHandler{evt_type, handler, filter, precedence, propagate_evt} );
      }

    private:

      /**
       * poll()
       * runs asynchronously in its own thread, waits for input, 
       * and notifies the main event loop if redrawing is necessary
       */
      void poll(){
        //wait for event
        bool quit = false;
        sf::Event evt;

        //is there a new event this frame?
        if (!win_.pollEvent(evt))
          return;

        //is that event the user closing?
        if (evt.type == sf::Event::Closed){
          exit();
          quit = true;
        }

        //else map it to our internal events
        Event e = txEvt(evt);
        //auto pos = sf::Mouse::getPosition(win_);
        //e.y = pos.y;
        //e.x = pos.x;

        //go through subscribers
        for ( auto& EH : EvtHandlers_){
          if (EH.type == e.e && EH.filter(e)){
            EH.handle(e);
            quit = !EH.propagate;
          }
          if (quit)
            break;
        }
      }

      GameApp() {
        gameRunning_ = true;
      }

      void update(float dt){
        //game entities
        for (int i=0; i < gameObjs_.size(); ++i){
          gameObjs_[i]->update(dt);
          gameObjs_[i]->refresh();
        }
      }

      void draw(){
        win_.clear();
        
        for (auto& obj : gameObjs_){
          win_.draw(*(obj->impl->sprite_));
          //LOG_DEBUG("Drawing " + obj->impl->str());
        }

        win_.display();
      }

      
      // -- members --
      bool gameRunning_;  //is game running
      //singleton
      static GameApp* GameApp_instance_;
      // These are the only entities that are being drawn
      vector<GameObject*> gameObjs_;  //But game-related entites must be loaded/unloaded
      vector<EvtHandler> EvtHandlers_;  //But game-related entites must be loaded/unloaded
      sf::RenderWindow win_;
  };

  GameApp *GameApp::GameApp_instance_ = nullptr;



  //warning: this is terrible:
   void GameObject::subscribe(const EType evt_type, 
                           std::function<void(const Event &e)> handler,
                           std::function<bool(const Event &e)> filter,
                           int precedence,
                           bool propagate_evt){
    GameApp::instance().subscribe_event(evt_type, handler, filter, precedence, propagate_evt);
  }

}
