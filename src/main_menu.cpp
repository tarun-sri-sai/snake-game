#include "main_menu.hpp"
#include "game_play.hpp"

MainMenu::MainMenu(std::shared_ptr<GameContext>& t_context) :
    m_context(t_context),
    m_gameTitle(t_context->assets->getFont(TITLE_FONT), "Snake Game", 60),
    m_playButton(sf::Text(m_context->assets->getFont(MENU_FONT), "Press [Enter] to play")),
    m_playButtonSelected(false),
    m_elapsedTime(sf::Time::Zero)
{
    m_gameTitle.setOrigin(m_gameTitle.getLocalBounds().getCenter());
    m_gameTitle.setPosition({
        m_context->window->getSize().x / 2.0f,
        m_context->window->getSize().y / 2.0f - 150.0f });

    m_playButton.setOrigin(m_playButton.getLocalBounds().getCenter());
    m_playButton.setPosition({
        m_context->window->getSize().x / 2.0f,
        m_context->window->getSize().y / 2.0f });
}

void MainMenu::listen()
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
            case sf::Keyboard::Key::Enter:
                m_playButtonSelected = true;
                break;
            case sf::Keyboard::Key::Escape:
                m_context->window->close();
                break;
            }
        }
    }
}

void MainMenu::update(const sf::Time& t_deltaTime)
{
    m_elapsedTime += t_deltaTime;
    if (m_elapsedTime.asSeconds() < Engine::TICK_TIME)
    {
        return;
    }

    if (m_playButtonSelected)
    {
        m_context->states->add(std::make_unique<GamePlay>(m_context));
        m_playButtonSelected = false;
    }

    m_elapsedTime -= sf::seconds(Engine::TICK_TIME);
}

void MainMenu::present()
{
    m_context->window->clear();

    m_context->window->draw(m_gameTitle);
    m_context->window->draw(m_playButton);

    m_context->window->display();
}
