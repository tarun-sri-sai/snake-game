#ifndef GAME_PLAY_HPP
#define GAME_PLAY_HPP

#include "state.hpp"
#include "game.hpp"
#include <memory>
#include <SFML/Graphics/Sprite.hpp>
#include <array>
#include "snake.hpp"
#include <random>

enum SnakeDirections
{
    UP = 0,
    DOWN,
    LEFT,
    RIGHT
};

class GamePlay : public Engine::State
{
public:
    GamePlay(std::shared_ptr<GameContext>& t_context);
    ~GamePlay() = default;

    void listen() override;
    void update(const sf::Time& t_deltaTime) override;
    void present() override;
private:
    std::shared_ptr<GameContext> m_context;
    sf::Sprite m_grass;
    sf::Sprite m_food;
    std::array<sf::Sprite, 4> m_walls;
    Snake m_snake;
    int m_snakeDirection;
    sf::Time m_elapsedTime;
    static std::random_device rd;
    std::mt19937 m_generator;
    int m_score;

    int getRandom(int t_min, int t_max);
    void setFoodPosition();
    sf::Vector2f getSnakeDirection();
    bool isSnakeOnWall();
};

#endif  // !GAME_PLAY_HPP
