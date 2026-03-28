#ifndef STATE_HPP
#define STATE_HPP

#include <SFML/System.hpp>

namespace Engine
{
    const float TICK_TIME = 0.12f;

    class State
    {
    public:
        State() {};
        virtual ~State() {};

        virtual void listen() = 0;
        virtual void update(const sf::Time& t_deltaTime) = 0;
        virtual void present() = 0;
    };
}

#endif  // !STATE_HPP
