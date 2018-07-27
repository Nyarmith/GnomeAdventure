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
        if (!GameApp_instance)
          GameApp_instance = new GameApp();
        return *GameApp_instance;
      }


      /**
       * run()
       * runs the GameApp given its setup entities
       */
      void run(){
        win_.create(sf::VideoMode(RESX, RESY), "GnomeAdventure");

        std::unique_lock<std::mutex>  l( nf_mtx_);
        std::thread input_thread(&GameApp::handle_input, this);
        while(gameRunning_){

          if(newframe_){
            newframe_ = false;
            draw();
            xt::usleep( DELAY );
          } else {
            no_newframe_.wait(l);
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

      void forceDraw(){ newframe_ = true; no_newframe_.notify_one(); };
      void newGUI(){ std::vector<GameObject*> t; GUIObjects_.push(t); }
      void popGUI(){ GUIObjects_.pop(); }
      void addGUI(GameObject *o){ GUIObjects_.top().push_back(o); };
      void addObj(GameObject *o){ gameObjs_.push_back(o); }

    private:

      /**
       * handle_input()
       * runs asynchronously in its own thread, waits for input, 
       * and notifies the main event loop if redrawing is necessary
       */
      void handle_input(){
        //wait for event
        while (gameRunning_){
          bool update = false;
          sf::Event evt;
          win_.waitEvent(evt);
          //is user closing?
          if (evt.type == sf::Event::Closed){
            exit();
            update = true;
          }

          //process events
          Event e = txEvt(evt);
          auto pos = sf::Mouse::getPosition(win_);
          e.y = pos.y;
          e.x = pos.x;

          //game entities
          if (GUIObjects_.size() <= 1){
            for (int i=0; i < gameObjs_.size(); ++i){
              if (!update && gameObjs_[i]->intersect(e.x,e.y)){
                gameObjs_[i]->handle(e);
                update = gameObjs_[i]->refresh();
              }
            }
          }

          //GUI entities
          if (!GUIObjects_.empty()){
            auto &set = GUIObjects_.top();
            for (int i=0; i<set.size(); ++i){
              if (!update && set[i]->intersect(e.x,e.y)){
                set[i]->handle(e);
                update = set[i]->refresh();
              }
            }
          }


          //attempt to wake mutex if it cares
          if (update){
            newframe_ = true;
            no_newframe_.notify_one();
          }
        }
      }

      std::atomic<bool> gameRunning_;

      GameApp() {
        gameRunning_ = true;
        newframe_ = true;
      }

      void update(Event e){
        //am I in the top-most gui?
      }

      void draw(){
        //clear screen
        win_.clear(sf::Color::White);
        
        //game entities
        if (GUIObjects_.size() <= 1){
          for (int i=0; i < gameObjs_.size(); ++i){
            //sfml draw
            win_.draw(*gameObjs_[i]->sprite_);
          }
        }

        //GUI entities
        if (!GUIObjects_.empty()){
          auto &set = GUIObjects_.top();
          for (int i=0; i<set.size(); ++i){
            win_.draw(*set[i]->sprite_);
          }
        }
        win_.display();
      }

      //mutex-related
      std::condition_variable no_newframe_;
      std::mutex nf_mtx_;
      std::atomic<bool> newframe_;

      //singleton
      static GameApp* GameApp_instance;

      // These are the only entities that are being drawn
      std::stack< std::vector<GameObject*> > GUIObjects_;  //GUIs can overalp indefinitely
      vector<GameObject*>                    gameObjs_;    //But game-related entites must be loaded/unloaded


      //sfml objects
      sf::RenderWindow win_;
  };

  GameApp *GameApp::GameApp_instance = 0;

}
