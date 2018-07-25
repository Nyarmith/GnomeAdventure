#include "common.hpp"

namespace ay{
  class AudioStore{
    public:
      void load_sound(string regName, string filePath);
      void load_track(string regName, string filePath);
      void play_sound(string regName);
      void play_track(string regName);

      AudioStore();
      ~AudioStore();
    private:
      std::map<std::string, sf::SoundBuffer> sounds;
      std::map<std::string, sf::Music> tracks;
  };
}
