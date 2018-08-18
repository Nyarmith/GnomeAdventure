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
    void set_pos(sf::Vector2f p);

    /** set_pos(x,y)
     *  Gets the current sprite position, relative to the top-left part of the screen */
    sf::Vector2f get_pos();

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
     * subscribe(const Event &e)
     * subscribe to an event type and define what your object does when it happens */
    virtual void subscribe(const EType evt_type, 
                           std::function<void(const Event &e)> handler,
                           std::function<bool(const Event &e)> filter = [](auto in){return true;},
                           int precedence=0,
                           bool propagate_evt=true);


    virtual bool intersect(int x, int y);

  private:
    GameObjectImpl* impl;
    bool refresh();
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

  void GameObject::set_pos(sf::Vector2f p)  {
    impl->set_pos(p.x,p.y);
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

  //TODO: Replace sf::Vector with something else
  sf::Vector2f GameObject::get_pos(){
    return impl->get_pos();
  }

  GameObject::~GameObject(){ delete impl; }
}

