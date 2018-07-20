## Engine Structure

As mentioned below, the main loop is something roughly as:

```
std::thread inputs(&input_thread);
while (gameRunning){
  renderMutex.lock();    //is there something new to draw?
  draw();
  renderMutex.unlock();
}
```

In this document we're going to tie-in entities, animations, click-handling and the refresh-loop

#### Entities and Events

All entities are sprites. They are composed of one texture, which is an part of the Entity constructor. If there is are multiple possible frames, then the texture must compose all the frames. The frames in a texture are enumerated starting from 0 in a row-major order (left-right, row-by-row). The frame number is used in the .draw() method of the entity.

Entities make the game aware by updating the draw mutex if there is something new to draw.

##### Entity Methods
```
//set absolute position and rotation angle
.setpos(x,y);
.setrot();

//move relative to current position
.move(x,y);
.move(sf::vec2(x,y)); //setpos also overloads for sf::vec2
.rotate(degree=3.14/2.0);

//drawing functions
.draw(frameNum);
.draw(); //defaults to 0th frame

//logic function
.handle(); //method to override to determine how events are handled
```


#### Click-Handling and the GUI Stack
Clicks are handled by the top-most stack of the GUI. In other words, if the GUI stack is larger than 1, then no game-entity events are handled, just gui entities. Each GUI frame is made up of entities.

Each gui element handles events independently, as such there is no "form" interface.

Some convenience gui objects have been added for the sake of easy text-based prototyping

##### Default gui elements:
- GUIMultChoice object to specify multiple-choice objects
- GUIToggle object for toggelable states
- GUIExit object to pop the current GUI frame
