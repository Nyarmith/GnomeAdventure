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
      std::thread input_thread();
      std::thread animation_thread();
      while(gameRunning){
        renderLock.lock();
        draw();
        renderLock.unlock();
        usleep( DELAY );
      }
    }

    /**
     * exit()
     * safely ends the application
     */
    void exit(){
      gameRunning = false;
    }

  private:
    static GameApp* GameApp_instance;

    // These are the only entities that are being drawn
    std::stack< std::queue<GUIObject> > GUI;  //GUIs can overalp indefinitely
    vector<GameObject> gameObjs;              //But game-related entites must be loaded/unloaded

    // Loop Flow Mutex Locks
    std::mutex renderLock;
    std::mutex animateLock;

    bool gameRunning;

    GameApp(){
      gameRunning = true;
    }

    void update(Event e){
      //am I in the top-most gui?
    }

    void draw(){
    }
};

GameApp *GameApp::GameApp_instance = 0;

