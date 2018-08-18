#include "GUIObject.hpp"
#include "AudioStore.hpp"

const long long DELAY = 25;
const long long RESX  = 1024;
const long long RESY  = 768;

//TODO: Hide implementation details of GameApp, possibly even factor out dependency w/ GameObjectImpl

namespace ay{
  class GameApp{
    public:
      /**
       * instance()
       * Gets instance of the game being run
       */
      static GameApp& instance(){
        if (!GameApp_instance_)
          GameApp_instance_ = new GameApp();
        return *GameApp_instance_;
      }

      /**
       * run()
       * runs the GameApp given its setup entities
       */
      void run(){
        win_.create(sf::VideoMode(RESX, RESY), "GnomeAdventure");

        LOG_DEBUG("Created window");

        sf::Clock timer;
        while(gameRunning_){

          float dt = timer.getElapsedTime().asSeconds();
          poll();
          update(dt);
          draw();
          xt::usleep( DELAY - dt );
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

    private:

      /**
       * poll()
       * runs asynchronously in its own thread, waits for input, 
       * and notifies the main event loop if redrawing is necessary
       */
      void poll(){
        //wait for event
        bool update = false;
        sf::Event evt;

        //is there a new event this frame?
        if (!win_.pollEvent(evt))
          return;

        //is that event the user closing?
        if (evt.type == sf::Event::Closed){
          exit();
          update = true;
        }

        //else map it to our internal events
        Event e = txEvt(evt);
        auto pos = sf::Mouse::getPosition(win_);
        e.y = pos.y;
        e.x = pos.x;

        //find first guy that intersects
        for (int i=0; i < gameObjs_.size(); ++i){
          if (!update && gameObjs_[i]->intersect(e.x,e.y)){
            gameObjs_[i]->handle(e);
            update = gameObjs_[i]->refresh();
          }
        }
      }


      GameApp() {
        gameRunning_ = true;
      }

      void update(float dt){
        //game entities
        for (int i=0; i < gameObjs_.size(); ++i){
          gameObjs_[i]->update(dt);
        }

      }

      void draw(){
        //clear screen
        win_.clear();
        
        //game entities
        for (auto& obj : gameObjs_){
          //sfml draw
          win_.draw(*(obj->impl->sprite_));
          LOG_DEBUG("Drawing " + obj->impl->str());
        }

        win_.display();
      }

      
      // -- members --
      bool gameRunning_;  //is game running
      //singleton
      static GameApp* GameApp_instance_;
      // These are the only entities that are being drawn
      vector<GameObject*> gameObjs_;  //But game-related entites must be loaded/unloaded
      sf::RenderWindow win_;
  };

  GameApp *GameApp::GameApp_instance_ = 0;

}
