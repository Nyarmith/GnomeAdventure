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
Main feature of the engine is that it doesn't redraw things unless necessary.

The structure is thus reflected as such:
* Animations are handled by a state-machine object

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
- Try something nicer than a pointer vector for objects maybe
- Input handler
- Make virtual handle() method in GameAPp
- Let objects subscribe to certain kinds of click events
- Fix drawing issue
- Separate source more nicely (ask Chris about this)
- Think through input handling more thoroughly
- Think through resolution scaling more thoroughly
- Add logging
- Add benchmarks
