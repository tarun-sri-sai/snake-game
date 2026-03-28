#ifndef MAIN_MENU_HPP
#define MAIN_MENU_HPP

#include "state.hpp"
#include "game.hpp"
#include <memory>
#include <SFML/Graphics/Text.hpp>
#include <array>

class MainMenu : public Engine::State
{
public:
    MainMenu(std::shared_ptr<GameContext>& t_context);
    ~MainMenu() = default;

    void listen() override;
    void update(const sf::Time& t_deltaTime) override;
    void present() override;
private:
    std::shared_ptr<GameContext> m_context;
    sf::Text m_gameTitle;
    sf::Text m_playButton;
    bool m_playButtonSelected;
    sf::Time m_elapsedTime;
};

#endif  // !MAIN_MENU_HPP
