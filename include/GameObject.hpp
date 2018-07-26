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
      GameObject(string texFile, sf::IntRect spriteDim){
        sf::Texture t;
        if (!t.loadFromFile(texFile))
          throw new std::runtime_error(std::string("ERR: file could not be loaded into texture:") + texFile);
      };
      GameObject(string texFile){};
      GameObject(){};
      virtual ~GameObject(){};

      /**
       * set_sprite(frameNum)
       * Sets the currently displayed sprite
       */

      void set_sprite(int spriteNum){
        if (tex_.find(spriteNum) == tex_.end()) throw new std::domain_error("ERR: Invalid set_sprite index");
        if (spriteNum != fnum_){
          update_ = true;
        }
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

      bool operator< (const GameObject &o){
        return precedence_ > o.precedence_;
      }

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
      int precedence_;
      std::map<int,sf::Sprite> tex_;

    private:
      sf::Sprite *sprite_;
      bool update_;
      bool refresh(){
        bool ret = update_ == true;
        update_ = false;
        if (ret){
          sprite_ = &tex_[fnum_];
          sprite_->setPosition(pos_.x, pos_.y);
          sprite_->setScale(dim_.x,dim_.y);
          sprite_->setRotation(rot_);
        }
        return ret;
      }

      virtual bool intersect(int x, int y){
        return (pos_.x <= x && x <= pos_.x + dim_.x &&
            pos_.y <= y && y <= pos_.y + dim_.y);
      }

      friend class GameApp;
  };
}
