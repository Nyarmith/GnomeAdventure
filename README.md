# GnomeAdventure

### Project Organization
This project is broken up into:
-sfml event-based game fmwk
-a game that uses that fmwk

### Separation of Responsibilities
Game-Engine:
- Handles gui rendering, prioritization, event-handling and abstractions
- Has a GameObject abstraction to encapsulate a drawable non-gui thing
- Handles only drawing when necessary (e.g. there was a relevant event or animation)
- Handles Audio info loading/storing in AudioStore
- Gives the user a small subset of possible input

GnomeAdventure Game:
- Defines a scene abstraction to encapsulate a single screen in the game
- Creates a GameState and Player classes to encapsulate global game-state and player-state information
- Uses GameObjects, GUIObjects, AudioStore to define/use the assets in the game


## Game-Engine Structure
The fmwk is asynchronous and assumes there will mostly be the same screen, perhaps with a few animations, as such the main render loop waits for new things to happen before it redraws a scene. New things to draw can be introduced either via user input (e.g. a menu click) or specific animations (e.g. clicking on an object makes it spin for a few frames)

The structure is thus reflected as such:
* User input is handled in its own thread
* Animations are handled in their own thread

The main loop is thus structured roughly as follows:
```
std::thread inputs(&input_thread);
std::thread animations(&animation_thread);
while (gameRunning){
  renderMutex.lock();    //is there something new to draw?
  draw();
  renderMutex.unlock();
}
```

TODO:
- Think through input handling more thoroughly
- Think through resolution scaling more thoroughly
- Add logging
- Add benchmarks
