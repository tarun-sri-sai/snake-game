#include "asset_manager.hpp"

Engine::AssetManager::~AssetManager()
{
    m_textures.clear();
    m_fonts.clear();
}

void Engine::AssetManager::addTexture(int t_id, const std::string& t_filePath, bool t_repeated)
{
    auto texture{ std::make_unique<sf::Texture>() };

    if (texture->loadFromFile(t_filePath))
    {
        texture->setRepeated(t_repeated);
        m_textures[t_id] = std::move(texture);
    }
}

void Engine::AssetManager::addFont(int t_id, const std::string& t_filePath)
{
    auto font{ std::make_unique<sf::Font>() };

    if (font->openFromFile(t_filePath))
    {
        m_fonts[t_id] = std::move(font);
    }
}

const sf::Texture& Engine::AssetManager::getTexture(int t_id) const
{
    return *(m_textures.at(t_id).get());
}

const sf::Font& Engine::AssetManager::getFont(int t_id) const
{
    return *(m_fonts.at(t_id).get());
}
