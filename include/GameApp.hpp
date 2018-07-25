#include "GameObject.hpp"
#include "GUIObject.hpp"
#include "AudioStore.hpp"

const long long DELAY = 25;

namespace ay{
  class GameApp{
    public:
      /**
       * instance()
       * Gets instance of the game being run
       */
      static GameApp& instance(){
        if (!GameApp_instance)
          GameApp_instance = new GameApp();
        return *GameApp_instance;
      }


      /**
       * run()
       * runs the GameApp given its setup entities
       */
      void run(){

        std::unique_lock<std::mutex>  l( nf_mtx_);
        std::thread input_thread(&GameApp::handle_input, this);
        while(gameRunning_){

          if(newframe_){
            newframe_ = false;
            draw();
            xt::usleep( DELAY );
          } else {
            no_newframe_.wait(l, [this](){ return newframe_ != false;} ); //TODO: change condition variable to another atomic operation
          }
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

    private:

      /**
       * handle_input()
       * runs asynchronously in its own thread, waits for input, 
       * and notifies the main event loop if redrawing is necessary
       */
      void handle_input(){
        //wait for event
        sf::Event evt;
        win_.waitEvent(evt);
        //is user closing?
        if (evt.type = sf::Event::Closed){
          win_.close();
        }

        //process events
        Event e = txEvt(evt);
        auto pos = sf::Mouse::getPosition(win_);
        e.y = pos.y;
        e.x = pos.x;

        bool update = false;
        //TODO: Update entities and handle updates on top-most stack
        //set newframe_ to true if something triggers a new frame


        //attempt to wake mutex if it cares
        if (update){
          newframe_ = true;
          std::unique_lock<std::mutex>  l( nf_mtx_);
        }
      }

      bool gameRunning_;

      GameApp(){
        gameRunning_ = true;
      }

      void update(Event e){
        //am I in the top-most gui?
      }

      void draw(){
      }

      //mutex-related
      std::condition_variable no_newframe_;
      std::mutex nf_mtx_;
      std::atomic<bool> newframe_;

      //singleton
      static GameApp* GameApp_instance;

      // These are the only entities that are being drawn
      std::stack< std::queue<GUIObject> > GUIObjects_;  //GUIs can overalp indefinitely
      vector<GameObject>                  gameObjs_;    //But game-related entites must be loaded/unloaded


      //sfml objects
      sf::Window win_;
  };

  GameApp *GameApp::GameApp_instance = 0;

}
