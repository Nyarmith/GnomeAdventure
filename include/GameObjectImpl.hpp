#include "common.hpp"
#include "Event.hpp"

namespace ay{

  struct GameObjectImpl{
    bool operator< (const GameObjectImpl &o){
      return precedence_ > o.precedence_;
    }

    sf::Vector2u dim_; //dimensions of current texture
    sf::Vector2i pos_{0,0};
    sf::Vector2i scale_{1,1};
    float rot_{0};
    int fnum_{-1};
    int precedence_{5};

    std::map<int,sf::Sprite> spr_;
    std::map<int,sf::Texture> tex_;
    sf::Sprite *sprite_;

    bool update_; //flag indicating redrawing is necessary


    void set_sprite(int spriteNum){
      if (tex_.find(spriteNum) == tex_.end()) throw new std::domain_error("ERR: Invalid set_sprite index");
      if (spriteNum != fnum_){
        update_ = true;
      }
      dim_ = tex_[spriteNum].getSize();
      fnum_ = spriteNum;
    };

    void set_pos(int x, int y)  { pos_ = sf::Vector2i(x,y); update_ = true; };

    void set_rot(float r) { rot_ = r; update_ = true;}

    void set_size(int w, int h) {
      scale_ = sf::Vector2i(
        w/static_cast<float>(dim_.x),
        h/static_cast<float>(dim_.y));

      update_ = true;
    };


    void register_sprite(string path_to_texture, int num){
      if (tex_.find(num) != tex_.end()) throw new std::domain_error("ERR: Texture index already taken");
      //TODO: Load sprits as per texture parameters you want with texture loading
      //TODO: A general texture pool would be sweet
      sf::Texture &t = tex_[num];
      if (!t.loadFromFile(path_to_texture))
        throw new std::runtime_error(std::string("ERR: file could not be loaded into texture:") + path_to_texture);
      spr_[num].setTexture(t);
      //spr_[num].setTextureRect(spriteDim);
    };


    void set_precedence(int num){
      precedence_ = num;
    }

    bool refresh(){
      bool ret = update_ == true;
      update_ = false;
      if (ret){
        sprite_ = &spr_[fnum_];
        sprite_->setPosition(pos_.x, pos_.y);
        sprite_->setScale(dim_.x,dim_.y);
        sprite_->setRotation(rot_);
      }
      return ret;
    }

    //TODO: remove this when input-handler is factored out
    virtual bool intersect(int x, int y){
      return (pos_.x <= x && x <= pos_.x + dim_.x &&
              pos_.y <= y && y <= pos_.y + dim_.y);
    }

    GameObjectImpl(string texFile){
      register_sprite(texFile, 0);
      set_sprite(0);
      refresh();
      //dim_ = sprite_->getTexture()->getSize(); //first texture determines default size
      update_ = true;
    };
  };
}
