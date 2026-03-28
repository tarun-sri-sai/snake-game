#include "state_manager.hpp"

Engine::StateManager::StateManager() : m_add(false), m_replace(false), m_remove(false)
{
}

Engine::StateManager::~StateManager()
{
    while (!m_states.empty())
    {
        m_states.pop();
    }
}

void Engine::StateManager::add(std::unique_ptr<State> t_state, bool t_replace)
{
    m_add = true;
    m_newState = std::move(t_state);
    m_replace = t_replace;
}

void Engine::StateManager::remove()
{
    m_remove = true;
}

void Engine::StateManager::update()
{
    if (m_remove && !m_states.empty())
    {
        m_states.pop();
        m_remove = false;
    }

    if (m_add)
    {
        if (m_replace && !m_states.empty())
        {
            m_states.pop();
        }

        m_states.push(std::move(m_newState));
        m_add = false;
    }
}

std::unique_ptr<Engine::State>& Engine::StateManager::get()
{
    return m_states.top();
}
