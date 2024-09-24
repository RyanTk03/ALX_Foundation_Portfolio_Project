#ifndef GAMEDATA_H
#define GAMEDATA_H

#include <fstream>
#include <SFML/Config.hpp>

class GameData
{
public:
    static GameData* load();
    static std::string data_location;
    GameData(GameData&) = delete;
    GameData& operator=(const GameData&) = delete;
    // TODO: [[nodiscard]] float getSoundVolume() const;
    // TODO: void setSoundVolume(float newVolume);
    // TODO: [[nodiscard]] float getMusicVolume() const;
    // TODO: void setMusicVolume(float newVolume);
    // TODO: void addToMoney(float amount);
    // TODO: [[nodiscard]] float getMoney() const;
    // TODO: [[nodiscard]] bool isSoundOn() const;
    // TODO: [[nodiscard]] bool isMusicOn() const;
    [[nodiscard]] sf::Int64 getPoint() const;
    void addToPoint(sf::Uint64 amount);
    void retrieveToPoint(sf::Uint64 amount);
    void save() const;

private:
    GameData(): m_point(0) {};
    // TODO: float m_sound_volume;
    // TODO: bool m_sound_on;
    // TODO: float m_music_volume;
    // TODO: bool m_music_on;
    // TODO: float m_money;
    sf::Int64 m_point;
};



#endif //GAMEDATA_H
