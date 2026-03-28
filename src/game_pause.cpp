#include "game_pause.hpp"

#define FMT_HEADER_ONLY
#include <fmt/format.h>

GamePause::GamePause(std::shared_ptr<GameContext>& t_context, int t_score) :
    m_context(t_context),
    m_titleText(t_context->assets->getFont(TITLE_FONT),
        "Paused", 60),
    m_scoreText(t_context->assets->getFont(MENU_FONT),
        fmt::format("Score: {}", t_score)),
    m_playButton(t_context->assets->getFont(MENU_FONT),
        "Press [Escape] to resume"),
    m_playButtonSelected(false),
    m_elapsedTime(sf::Time::Zero)
{
    m_titleText.setOrigin(m_titleText.getLocalBounds().getCenter());
    m_titleText.setPosition({
        m_context->window->getSize().x / 2.0f,
        m_context->window->getSize().y / 2.0f - 150.0f });

    m_scoreText.setOrigin(m_scoreText.getLocalBounds().getCenter());
    m_scoreText.setPosition({
        m_context->window->getSize().x / 2.0f,
        m_context->window->getSize().y / 2.0f });

    m_playButton.setOrigin(m_playButton.getLocalBounds().getCenter());
    m_playButton.setPosition({
        m_context->window->getSize().x / 2.0f,
        m_context->window->getSize().y / 2.0f + 60.0f });
}

void GamePause::listen()
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
            case sf::Keyboard::Key::Escape:
                m_playButtonSelected = true;
                break;
            }
        }
    }
}

void GamePause::update(const sf::Time& t_deltaTime)
{
    m_elapsedTime += t_deltaTime;
    if (m_elapsedTime.asSeconds() < Engine::TICK_TIME)
    {
        return;
    }

    if (m_playButtonSelected)
    {
        m_context->states->remove();
        m_playButtonSelected = false;
    }

    m_elapsedTime -= sf::seconds(Engine::TICK_TIME);
}

void GamePause::present()
{
    m_context->window->clear();

    m_context->window->draw(m_titleText);
    m_context->window->draw(m_scoreText);
    m_context->window->draw(m_playButton);

    m_context->window->display();
}
