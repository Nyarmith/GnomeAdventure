#include "GameObject.hpp"
#include "GUIObject.hpp"
#include "AudioStore.hpp"

const long long DELAY = 25;

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
          usleep( DELAY );
        } else {
          no_newframe_.wait(l, [this](){ return newframe_ != false;} );
        }
      }
    }

    /**
     * exit()
     * safely ends the application
     */
    void exit(){
      gameRunning_ = false;
    }

  private:

    void handle_input(){
      //wait for event
      
      //process events
      
      //attempt to wake mutex if it cares
      std::unique_lock<std::mutex>  l( nf_mtx_);
    }

    std::condition_variable no_newframe_;
    std::mutex nf_mtx_;
    bool newframe_;
    static GameApp* GameApp_instance;

    // These are the only entities that are being drawn
    std::stack< std::queue<GUIObject> > GUI;  //GUIs can overalp indefinitely
    vector<GameObject> gameObjs;              //But game-related entites must be loaded/unloaded

    // Loop Flow Mutex Locks
    std::mutex renderLock;
    std::mutex animateLock;

    bool gameRunning_;

    GameApp(){
      gameRunning_ = true;
    }

    void update(Event e){
      //am I in the top-most gui?
    }

    void draw(){
    }
};

GameApp *GameApp::GameApp_instance = 0;

