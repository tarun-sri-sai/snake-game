#ifndef STATE_MANAGER_HPP
#define STATE_MANAGER_HPP

#include <stack>
#include "state.hpp"
#include <memory>

namespace Engine
{
    class StateManager
    {
    public:
        StateManager();
        ~StateManager();

        void add(std::unique_ptr<State> t_state, bool t_replace = true);
        void remove();
        void update();
        std::unique_ptr<State>& get();
    private:
        std::stack<std::unique_ptr<State>> m_states;
        std::unique_ptr<State> m_newState;
        bool m_add;
        bool m_replace;
        bool m_remove;
    };
}

#endif  // !STATE_MANAGER_HPP
