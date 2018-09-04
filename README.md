# GnomeAdventure

### Project Organization
This project is broken up into:
-sfml event-based game fmwk
-a game that uses that fmwk

### Separation of Responsibilities
Game-Engine:
- Tailored towards sierra-style adventure games and visual novels
- Tries to handle drawing only drawing when necessary (e.g. there was a relevant event or animation)
- Audio done in singleton

GnomeAdventure Game:
- Defines a scene abstraction to encapsulate a single screen in the game
- Creates a GameState and Player classes to encapsulate global game-state and player-state information
- Uses GameObjects, GUIObjects, AudioStore to define/use the assets in the game


TODO:
- Try something nicer than a pointer vector for objects maybe
- Adventure-specific abstractions
- agf-specific abstractions
- Add better logger
- Let objects subscribe to certain kinds of click events
- Separate source more nicely (ask Chris about his opinion)
- Make virtual handle() method in GameApp (maybe)
- Think through resolution scaling more thoroughly
- Benchmarks
