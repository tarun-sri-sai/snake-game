#include "Snake.hpp"

Snake::Snake(const sf::Texture& t_texture) :
    m_body(std::list<sf::Sprite>(3, sf::Sprite(t_texture)))
{
    m_head = --m_body.end();
    m_tail = m_body.begin();
    
    float x = 16.0f;
    for (auto& piece : m_body)
    {
        piece.setPosition({ x, 16.0f });
        x += 16.0f;
    }
}

Snake::~Snake()
{
    m_body.clear();
}

void Snake::move(const sf::Vector2f& t_direction)
{
    m_tail->setPosition(m_head->getPosition() + t_direction);
    m_head = m_tail;
    ++m_tail;

    if (m_tail == m_body.end())
    {
        m_tail = m_body.begin();
    }
}

bool Snake::isHeadOn(const sf::Sprite& t_other) const
{
    return t_other.getGlobalBounds().findIntersection(m_head->getGlobalBounds()).has_value();
}

bool Snake::isOn(const sf::Sprite& t_other) const
{
    for (auto& piece : m_body)
    {
        if (t_other.getGlobalBounds().findIntersection(piece.getGlobalBounds()).has_value())
        {
            return true;
        }
    }
    return false;
}

bool Snake::isDead() const
{
    for (std::list<sf::Sprite>::const_iterator piece = m_body.begin(); piece != std::prev(m_body.end(), 2); ++piece)
    {
        if (piece != m_head && isHeadOn(*piece))
        {
            return true;
        }
    }
    return false;
}

void Snake::grow(const sf::Vector2f& t_direction)
{
    sf::Sprite newPiece(m_body.begin()->getTexture());
    newPiece.setPosition(m_head->getPosition() + t_direction);

    m_head = m_body.insert(++m_head, newPiece);
}

void Snake::draw(sf::RenderTarget& t_target, sf::RenderStates t_states) const
{
    for (auto& piece : m_body)
    {
        t_target.draw(piece);
    }
}
