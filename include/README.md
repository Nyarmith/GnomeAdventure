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

#### Click-Handling and the GUI Stack

#### Refresh-Loop, Animations, and Re-Drawing


### Putting it All Together
