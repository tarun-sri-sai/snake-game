#ifndef GAME_HPP
#define GAME_HPP

#include "asset_manager.hpp"
#include "state_manager.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>
#include <filesystem>

namespace fs = std::filesystem;

enum GameAssets
{
    TITLE_FONT = 0,
    MENU_FONT,
    GRASS,
    FOOD,
    WALL,
    SNAKE
};

struct GameContext
{
    std::unique_ptr<Engine::AssetManager> assets;
    std::unique_ptr<Engine::StateManager> states;
    std::unique_ptr<sf::RenderWindow> window;

    GameContext()
    {
        assets = std::make_unique<Engine::AssetManager>();
        states = std::make_unique<Engine::StateManager>();
        window = std::make_unique<sf::RenderWindow>();
    }
};

const fs::path ASSETS_DIR = fs::path("assets");

class Game
{
public:
    Game();
    ~Game() = default;

    void run();
private:
    std::shared_ptr<GameContext> m_context;
    const sf::Time FRAME_TIME = sf::seconds(1.0f / 60.0f);

    std::string getAssetFile(const std::string& t_fileName);
};

#endif  // !GAME_HPP
