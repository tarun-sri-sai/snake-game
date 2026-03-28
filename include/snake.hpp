#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <list>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

class Snake : public sf::Drawable
{
public:
    Snake(const sf::Texture& t_texture);
    ~Snake();

    void move(const sf::Vector2f& t_direction);
    bool isOn(const sf::Sprite& t_other) const;
    bool isHeadOn(const sf::Sprite& t_other) const;
    void grow(const sf::Vector2f& t_direction);
    void draw(sf::RenderTarget& t_target, sf::RenderStates t_states) const override;
    bool isDead() const;
private:
    std::list<sf::Sprite> m_body;
    std::list<sf::Sprite>::iterator m_head;
    std::list<sf::Sprite>::iterator m_tail;
};

#endif    // !SNAKE_HPP
