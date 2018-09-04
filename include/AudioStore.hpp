#include "common.hpp"

namespace ay{
  class AudioStore{
  public:
    //---- INTERFACE BEGIN ----

    //get handle to AudioStore
    static AudioStore& instance();

    //#create new sounds and tracks in registers
    void load_sound(string regName, string filePath);
    void load_track(string regName, string filePath);

    //#play arbitrary audio or sounds with or without looping
    void play_sound(string regName, bool loop=false);
    void play_track(string regName, bool loop=false);

    //#stopping sounds (causes them to reset from beginning on next play)
    void stop_sound(string regName);
    void stop_track(string regName);

    //#pause audio option for bg, can be resumed with play_track
    void pause_track(string regName);

    //---- INTERFACE END ----
  private:
    std::string curTrack{""};
    std::unordered_map<std::string, std::pair<sf::SoundBuffer,sf::Sound>> sounds;
    std::unordered_map<std::string, sf::Music> tracks;
    void loadErr(string filePath) { throw ("Error, could not load " + filePath); };
    void keyErr(string regName) { throw ("Error, no such audio in memory " + regName); };
    static AudioStore* AudioStore_instance;
    AudioStore() {};
    ~AudioStore() {};
  };

  void AudioStore::load_sound(string regName, string filePath)
  {
    if (!sounds[regName].first.loadFromFile(filePath))
      loadErr(filePath);
  }

  void AudioStore::load_track(string regName, string filePath)
  {
    if(!tracks[regName].openFromFile(filePath))
      loadErr(filePath);
  }

  void AudioStore::play_sound(string regName, bool loop)
  {
    if (sounds.find(regName) == sounds.end())
      keyErr(regName);

    sf::SoundBuffer &sndbuf = sounds[regName].first;
    sf::Sound &snd = sounds[regName].second;
    snd.setBuffer(sndbuf);
    snd.setLoop(loop);
    snd.play();
  }

  //only one music track may be playing at one time
  void AudioStore::play_track(string regName, bool loop)
  {
    if (tracks.find(regName) == tracks.end())
      keyErr(regName);

    sf::Music &music = tracks[regName];
    music.setLoop(loop);
    music.play();
  }

  void AudioStore::stop_sound(string regName)
  {
    if (sounds.find(regName) == sounds.end())
      keyErr(regName);

    sf::Sound &snd = sounds[regName].second;
    snd.stop();
    snd.setLoop(false); //reset loop on stop
  }

  void AudioStore::stop_track(string regName)
  {
    if (tracks.find(regName) == tracks.end())
      keyErr(regName);

    sf::Music &music = tracks[regName];
    music.stop();
    music.setLoop(false);
  }
  void AudioStore::pause_track(string regName)
  {
    if (tracks.find(regName) == tracks.end())
      keyErr(regName);

    sf::Music &music = tracks[regName];
    music.pause();
  }

  AudioStore& AudioStore::instance()
  {
    if(!AudioStore_instance)
      AudioStore_instance = new AudioStore;
    return *AudioStore_instance;
  }

  AudioStore *AudioStore::AudioStore_instance = nullptr;
}
