## Engine Structure

As mentioned below, the main loop is something roughly as:

```
std::thread inputs(&input_thread);
std::thread animations(&animation_thread);
while (gameRunning){
  renderMutex.lock();    //is there something new to draw?
  draw();
  renderMutex.unlock();
}
```

In this document we're going to tie-in entities, animations, click-handling and the refresh-loop

#### Entities and Events

All entities are sprites. They are composed of one texture, which is an part of the Entity constructor. If there is an animation, the texture must contain the animation frames. By default the animation is assumed to proceed left-right, row-by-row (not including the first frame, which is the default). Animations can loop or run once(by default).

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
//future TODO
.animate(frameList={1,2,4,3});
.animate(); //defaults to all other frames in row-column order

.handle(); //method to override to determine how events are handled
```


#### Click-Handling and the GUI Stack

#### Refresh-Loop, Animations, and Re-Drawing


### Putting it All Together
