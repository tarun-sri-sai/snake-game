#include "game_play.hpp"
#include <iostream>
#include "game_over.hpp"
#include "game_pause.hpp"

GamePlay::GamePlay(std::shared_ptr<GameContext>& t_context) :
    m_context(t_context),
    m_grass(m_context->assets->getTexture(GRASS)),
    m_food(m_context->assets->getTexture(FOOD)),
    m_walls{
        sf::Sprite(m_context->assets->getTexture(WALL)),
        sf::Sprite(m_context->assets->getTexture(WALL)),
        sf::Sprite(m_context->assets->getTexture(WALL)),
        sf::Sprite(m_context->assets->getTexture(WALL))
    },
    m_snake(m_context->assets->getTexture(SNAKE)),
    m_snakeDirection(RIGHT),
    m_elapsedTime(sf::Time::Zero),
    m_generator{ std::random_device{}() },
    m_score(0)
{
    m_grass.setTextureRect(m_context->window->getViewport(m_context->window->getDefaultView()));

    sf::Vector2u windowSize = m_context->window->getSize();

    m_walls[0].setTextureRect({ { 0, 0 }, { (int)windowSize.x, 16 } });
    m_walls[0].setPosition({ 0.0f, 0.0f });

    m_walls[1].setTextureRect({ { 0, 0 }, { (int)windowSize.x, 16 } });
    m_walls[1].setPosition({ 0.0f, (float)windowSize.y - 16.0f });

    m_walls[2].setTextureRect({ { 0, 0 }, { (int)windowSize.y - 32, 16 } });
    m_walls[2].setPosition({ 16.0f, 16.0f });
    m_walls[2].setRotation(sf::degrees(90));

    m_walls[3].setTextureRect({ { 0, 0 }, { (int)windowSize.y - 32, 16 } });
    m_walls[3].setPosition({ (float)windowSize.x, 16.0f });
    m_walls[3].setRotation(sf::degrees(90));

    setFoodPosition();
}

sf::Vector2f GamePlay::getSnakeDirection()
{
    switch (m_snakeDirection)
    {
    case UP:
        return { 0.f, -16.0f };
    case DOWN:
        return { 0.f, 16.0f };
    case LEFT:
        return { -16.0f, 0.0f };
    case RIGHT:
        return { 16.0f, 0.0f };
    default:
        return { 0.0f, 0.0f };
    }
}

void GamePlay::setFoodPosition()
{
    sf::Vector2f result = {
        (float)getRandom(1, (960 - 32) / 16) * 16,
        (float)getRandom(1, (540 - 32) / 16) * 16
    };
    m_food.setPosition(result);

    while (m_snake.isOn(m_food))
    {
        result = {
            (float)getRandom(1, (960 - 32) / 16) * 16,
            (float)getRandom(1, (540 - 32) / 16) * 16
        };
        m_food.setPosition(result);
    }
}

void GamePlay::listen()
{
    while (const std::optional event = m_context->window->pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            m_context->window->close();
        }
        else if (auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
        {
            switch (keyPressed->code)
            {
            case sf::Keyboard::Key::Up:
                if (m_snakeDirection != DOWN)
                {
                    m_snakeDirection = UP;
                }
                break;
            case sf::Keyboard::Key::Down:
                if (m_snakeDirection != UP)
                {
                    m_snakeDirection = DOWN;
                }
                break;
            case sf::Keyboard::Key::Left:
                if (m_snakeDirection != RIGHT)
                {
                    m_snakeDirection = LEFT;
                }
                break;
            case sf::Keyboard::Key::Right:
                if (m_snakeDirection != LEFT)
                {
                    m_snakeDirection = RIGHT;
                }
                break;
            case sf::Keyboard::Key::Escape:
                m_context->states->add(std::make_unique<GamePause>(m_context, m_score), false);
                break;
            }
        }
    }
}

void GamePlay::update(const sf::Time& t_deltaTime)
{
    m_elapsedTime += t_deltaTime;
    if (m_elapsedTime.asSeconds() < Engine::TICK_TIME)
    {
        return;
    }

    if (isSnakeOnWall() || m_snake.isDead() || m_score > 1392)
    {
        m_context->states->add(std::make_unique<GameOver>(m_context, m_score));
        return;
    }

    if (m_snake.isHeadOn(m_food))
    {
        m_score++;
        m_snake.grow(getSnakeDirection());
        setFoodPosition();
    }
    else
    {
        m_snake.move(getSnakeDirection());
    }

    m_elapsedTime -= sf::seconds(Engine::TICK_TIME);
}

bool GamePlay::isSnakeOnWall()
{
    for (auto& wall : m_walls)
    {
        if (m_snake.isHeadOn(wall))
        {
            return true;
        }
    }
    return false;
}

void GamePlay::present()
{
    m_context->window->clear();

    m_context->window->draw(m_grass);

    for (auto& wall : m_walls)
    {
        m_context->window->draw(wall);
    }

    m_context->window->draw(m_food);
    m_context->window->draw(m_snake);

    m_context->window->display();
}

int GamePlay::getRandom(int t_min, int t_max) {
    std::uniform_int_distribution<int> distribution(t_min, t_max);

    return distribution(m_generator);
}
