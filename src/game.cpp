#include "game.hpp"
#include <thread>
#include <chrono>
#include "main_menu.hpp"
using namespace std::chrono_literals;

Game::Game() : m_context(std::make_shared<GameContext>())
{
    m_context->window->create(sf::VideoMode({ 960, 544 }), "Snake Game", sf::Style::Close);

    m_context->assets->addFont(TITLE_FONT, getAssetFile("knight_warrior.otf"));
    m_context->assets->addFont(MENU_FONT, getAssetFile("supreme_spike.otf"));

    m_context->assets->addTexture(GRASS, getAssetFile("grass.png"), true);
    m_context->assets->addTexture(WALL, getAssetFile("wall.png"), true);
    m_context->assets->addTexture(FOOD, getAssetFile("food.png"));
    m_context->assets->addTexture(SNAKE, getAssetFile("snake.png"));

    m_context->states->add(std::make_unique<MainMenu>(m_context));
}

std::string Game::getAssetFile(const std::string& t_fileName)
{
    return (ASSETS_DIR / fs::path(t_fileName)).string();
}

void Game::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastFrame{ sf::Time::Zero };

    while (m_context->window->isOpen())
    {
        timeSinceLastFrame += clock.restart();

        if (timeSinceLastFrame < FRAME_TIME)
        {
            std::this_thread::sleep_for(5ms);
            continue;
        }

        while (timeSinceLastFrame >= FRAME_TIME)
        {
            timeSinceLastFrame -= FRAME_TIME;

            m_context->states->update();
            m_context->states->get()->listen();
            m_context->states->get()->update(FRAME_TIME);
            m_context->states->get()->present();
        }
    }
}
