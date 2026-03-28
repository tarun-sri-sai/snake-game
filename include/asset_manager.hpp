#ifndef ASSET_MANAGER_HPP
#define ASSET_MANAGER_HPP

#include <map>
#include <SFML/Graphics.hpp>

namespace Engine
{
    class AssetManager
    {
    public:
        AssetManager() = default;
        ~AssetManager();

        void addTexture(int t_id, const std::string& t_filePath, bool t_repeated = false);
        void addFont(int t_id, const std::string& t_filePath);

        const sf::Texture& getTexture(int t_id) const;
        const sf::Font& getFont(int t_id) const;
    private:
        std::map<int, std::unique_ptr<sf::Texture>> m_textures;
        std::map<int, std::unique_ptr<sf::Font>> m_fonts;
    };
}

#endif  // !ASSET_MANAGER_HPP
