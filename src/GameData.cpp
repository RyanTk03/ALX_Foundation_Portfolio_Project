#include "../inc/GameData.h"

std::string GameData::data_location = "../data/gameData.bin";

void GameData::save() const
{
    std::ofstream ofs(GameData::data_location);
    ofs << "point=" << this->m_point << std::endl;
    /* TODO:
        ofs << "money=" << this->m_money << std::endl;
        ofs << "sound_volume=" << this->m_sound_volume << std::endl;
        ofs << "music_volume=" << this->m_music_volume << std::endl;
        ofs << "music_on=" << (this->m_music_on ? "true" : "false") << std::endl;
        ofs << "sound_on=" << (this->m_sound_on ? "true" : "false") << std::endl;
    */
    ofs.close();
}

GameData* GameData::load()
{
    std::ifstream ifs(GameData::data_location);
    static auto data = new GameData();
    if (ifs.is_open()) {
        std::string line;
        while (std::getline(ifs, line)) {
            if (line.find("point=") == 0)
            {
                data->m_point = std::stoll(line.substr(6));
            }
            /* TODO:
                if (line.find("money=") == 0)
                {
                    data->m_money = std::stof(line.substr(6));
                }
                else if (line.find("sound_volume=") == 0)
                {
                    data->m_sound_volume = std::stof(line.substr(13));
                }
                else if (line.find("music_volume=") == 0)
                {
                    data->m_music_volume = std::stof(line.substr(13));
                } else if (line.find("music_on=") == 0)
                {
                    data->m_music_on = (line.substr(9) == "true");
                }
                else if (line.find("sound_on=") == 0)
                {
                    data->m_sound_on = (line.substr(9) == "true");
                }
            */
        }
        ifs.close();
    } else {
        /* TODO:
            data->m_money = 0.0f;
            data->m_sound_volume = 0.5f;
            data->m_music_volume = 0.5f;
            data->m_music_on = true;
            data->m_sound_on = true;
        */
        data->m_point = 0;
        data->save();
    }
    return data;
}

/* TODO:
    float GameData::getSoundVolume() const
    {
        return this->m_sound_volume;
    }
    float GameData::getMusicVolume() const
    {
        return this->m_music_volume;
    }
    float GameData::getMoney() const
    {
        return this->m_money;
    }
    bool GameData::isMusicOn() const
    {
        return this->m_music_on;
    }
    bool GameData::isSoundOn() const
    {
        return this->m_sound_on;
    }
    void GameData::setSoundVolume(float const newVolume)
    {
        this->m_sound_volume = newVolume;
    }
    void GameData::setMusicVolume(float const newVolume)
    {
        this->m_music_volume = newVolume;
    }
    void GameData::addToMoney(float const amount)
    {
        this->m_money += amount;
    }
*/

sf::Int64 GameData::getPoint() const
{
    return m_point;
}

void GameData::addToPoint(sf::Uint64 const amount)
{
    m_point += amount;
    this->save();
}

void GameData::retrieveToPoint(sf::Uint64 const amount)
{
    m_point -= amount;
    this->save();
}

