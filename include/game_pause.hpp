#ifndef GAME_PAUSE_HPP
#define GAME_PAUSE_HPP

#include "state.hpp"
#include "game.hpp"

class GamePause : public Engine::State
{
public:
    GamePause(std::shared_ptr<GameContext>& t_context, int t_score);
    ~GamePause() = default;

    void listen() override;
    void update(const sf::Time& t_deltaTime) override;
    void present() override;
private:
    std::shared_ptr<GameContext> m_context;
    sf::Text m_titleText;
    sf::Text m_scoreText;
    sf::Text m_playButton;
    bool m_playButtonSelected;
    sf::Time m_elapsedTime;
};

#endif GAME_PAUSE_HPP
