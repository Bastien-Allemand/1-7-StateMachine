#pragma once
#include <SFML/Graphics.hpp>

class Boudaries
{
	sf::FloatRect m_rect;
	sf::Vector2f m_distance_outside;

public:
	Boudaries();
	virtual void SetBoundaries(sf::FloatRect _rect);
	virtual void SetBoundaries(int _left, int _top, int _width, int _height);
	virtual void SetBoundaries(sf::Vector2f _position, sf::Vector2f _dimension);
	bool CheckBoundaries(sf::Vector2f _position);

	bool CheckBoundariesleft(sf::Vector2f _position);
	bool CheckBoundariesRight(sf::Vector2f _position);
	bool CheckBoundariesTop(sf::Vector2f _position);
	bool CheckBoundariesBottom(sf::Vector2f _position);

	sf::Vector2f GetDistanceOutside();
	sf::FloatRect GetBoundaries();
};

