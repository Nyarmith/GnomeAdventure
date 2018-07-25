#include "common.hpp"
#include "Event.hpp"

namespace ay{
  class GameObject{
    public:
      /**
       * GameObject()
       * Constructor that takes texture-path, dimension, position, rotation
       *
       */
      GameObject(string texture, sf::Vector2i dimension, sf::Vector2i pos, float rot);
      GameObject(string texture){};
      GameObject(){};
      ~GameObject(){};

      /**
       * set_sprite(frameNum)
       * Sets the currently displayed sprite
       */

      void set_sprite(int spriteNum){
        if (tex_.find(spriteNum) == tex_.end()) throw new std::domain_error("ERR: Invalid set_sprite index");
        if (spriteNum != fnum_)
          update_ = true;
        fnum_ = spriteNum;
      };

      /**
       * set_pos(x,y)
       * Sets the sprite position
       */
      void set_pos(int x, int y)  { pos_ = sf::Vector2i(x,y); update_ = true; };

      /**
       * set_size(h,w)
       * sets height and width of currently displayed sprite
       */
      void set_size(int w, int h) { dim_ = sf::Vector2i(w,h); update_ = true; };

      /**
       * register_sprite
       * loads a texture into a specified frame-number for later switching
       */
      void register_sprite(string path_to_texture, int num){
        if (tex_.find(num) != tex_.end()) throw new std::domain_error("ERR: Texture index already taken");
        //TODO: Load sprits as per texture parameters you want with texture loading
      };


    protected:
      /**
       * handle(const Event &e)
       * must be inherited to create object handler
       */
      virtual void handle(const Event &e) = 0;

      sf::Vector2i pos_;
      sf::Vector2i dim_;
      float rot_;
      int fnum_;
      std::map<int,sf::Texture> tex_;



      //private interface used by GameApp
    private:
      bool update_;
      bool refresh(){
        bool ret = update_ == true;
        update_ = false;
        return update_;
      }
  };
}
