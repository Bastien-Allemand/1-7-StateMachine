#include "Boudaries.h"

Boudaries::Boudaries()
{
	//Init
	m_rect = sf::FloatRect(0, 0, 0, 0);
	m_distance_outside = sf::Vector2f(0, 0);
}

void Boudaries::SetBoundaries(sf::FloatRect _rect)
{m_rect = _rect;}

void Boudaries::SetBoundaries(int _left, int _top, int _width, int _height)
{SetBoundaries(sf::FloatRect(_left, _top, _width, _height));}

void Boudaries::SetBoundaries(sf::Vector2f _position, sf::Vector2f _dimension)
{SetBoundaries(sf::FloatRect(_position, _dimension));}

bool Boudaries::CheckBoundaries(sf::Vector2f _position)
{
	bool isoutside = false;
	m_distance_outside = sf::Vector2f(0, 0);
	if (CheckBoundariesTop(_position))
		isoutside = true;
	if(CheckBoundariesBottom(_position))
		isoutside = true;
	if(CheckBoundariesleft(_position))
		isoutside = true;
	if(CheckBoundariesRight(_position))
		isoutside = true;

	return isoutside;
}

bool Boudaries::CheckBoundariesleft(sf::Vector2f _position)
{
	if (_position.x < m_rect.left)
	{
		m_distance_outside = sf::Vector2f(m_rect.left - _position.x, m_distance_outside.y);
		return true;
	}
	return false;
}

bool Boudaries::CheckBoundariesRight(sf::Vector2f _position)
{
	if (_position.x > m_rect.left + m_rect.width)
	{
		m_distance_outside = sf::Vector2f(m_rect.left + m_rect.width - _position.x, m_distance_outside.y);
		return true;
	}
	return false;
}

bool Boudaries::CheckBoundariesTop(sf::Vector2f _position)
{
	if (_position.y < m_rect.top)
	{
		m_distance_outside = sf::Vector2f(m_distance_outside.x, m_rect.top - _position.y);
		return true;
	}
	return false;
}

bool Boudaries::CheckBoundariesBottom(sf::Vector2f _position)
{
	if (_position.y > m_rect.top + m_rect.height)
	{
		m_distance_outside = sf::Vector2f(m_distance_outside.x, m_rect.top + m_rect.height - _position.y);
		return true;
	}
	return false;
}

sf::Vector2f Boudaries::GetDistanceOutside()
{return m_distance_outside;}

sf::FloatRect Boudaries::GetBoundaries()
{return m_rect;}
