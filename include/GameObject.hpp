#include "GameObjectImpl.hpp"

namespace ay{

  class GameObject{
  public:
    /** GameObject(textureFile)
     *  Takes the path to a texture*/
    GameObject(string path_to_texture);

    /** add_sprite(textureFile, frameNum)
     *  loads a sprite into a new frame-number to switch to later, frame_num must be untaken*/
    void register_sprite(string path_to_texture, int frame_num);

    /** set_sprite(frame_num)
     *  Changes the current sprite to the one loaded in frame_num */
    void set_sprite(int frame_num);

    /** set_pos(x,y)
     *  Sets the sprite position, relative to the top-left part of the screen */
    void set_pos(int x, int y);

    /** set_rot(r)
     *  Sets the rotation of the sprite in radians */
    void set_rot(float r);

    /** set_size(h,w)
     *  sets height and width of currently displayed sprite */
    void set_size(int w, int h);

    /** set_precedence(p)
     *  set order of drawing, higher = later */
    void set_precedence(int p);

    virtual ~GameObject();

  protected:
    /**
     * update(float dt)
     * override this to change object's action between frames */
    virtual void update(float dt) = 0;

    /**
     * handle(const Event &e)
     * override this to define how object handles input */
    virtual void handle(const Event &e) = 0;



  private:
    GameObjectImpl* impl;
    bool refresh();
    bool intersect(int x, int y);
    bool operator< (const GameObject &o);
    friend class GameApp;
  };



  GameObject::GameObject(string path_to_texture){
    impl = new GameObjectImpl(path_to_texture);
  };

  void GameObject::set_sprite(int spriteNum){
    impl->set_sprite(spriteNum);
  };

  void GameObject::set_pos(int x, int y)  {
    impl->set_pos(x,y);
  }

  void GameObject::set_rot(float r) {
    impl->set_rot(r);
  }

  void GameObject::set_size(int w, int h) {
    impl->set_size(w,h);
  };

  void GameObject::register_sprite(string path_to_texture, int num){
    impl->register_sprite(path_to_texture, num);
  };

  bool GameObject::refresh(){
    impl->refresh();
  }

  void GameObject::set_precedence(int num){
    impl->set_precedence(num);
  }


  bool GameObject::operator< (const GameObject &o){
    return *impl < *(o.impl);
  }

  //TODO: remove this when input-handler is factored out
  bool GameObject::intersect(int x, int y){
    return impl->intersect(x,y);
  }

  GameObject::~GameObject(){ delete impl; }
}

