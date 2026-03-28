#ifndef GAME_OVER_HPP
#define GAME_OVER_HPP

#include "state.hpp"
#include <SFML/Graphics/Text.hpp>
#include "game.hpp"

class GameOver : public Engine::State
{
public:
    GameOver(std::shared_ptr<GameContext>& t_context, int t_score);
    ~GameOver() = default;

    void listen() override;
    void update(const sf::Time& t_deltaTime) override;
    void present() override;
private:
    std::shared_ptr<GameContext> m_context;
    sf::Text m_titleText;
    sf::Text m_scoreText;
    sf::Text m_retryButton;
    bool m_retryButtonSelected;
    sf::Time m_elapsedTime;
};

#endif  // !GAME_OVER_HPP
