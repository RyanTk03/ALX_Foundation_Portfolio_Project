//
// Created by lenovo on 22/09/2024.
//

#ifndef CUSTOMCLOCK_H
#define CUSTOMCLOCK_H

#include <SFML/System.hpp>

class CustomClock {
public:

    CustomClock();

    void start();
    void pause();
    void reinitialize();

    [[nodiscard]] sf::Time getElapsedTime() const;

private:
    enum State {Started, Paused};

    sf::Clock m_clock;
    State m_state;
    sf::Time m_elapsed_time;
};



#endif //CUSTOMCLOCK_H
