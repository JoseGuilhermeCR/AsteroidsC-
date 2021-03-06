/*
 Author: JoseGuilhermeCR
 Copyright 2017
*/

#include "include/Asteroid.h"
#include "include/Utils.h"

Asteroid::Asteroid(float x, float y, float velX, float velY, float r, float total, float rotation, const std::vector<int> &offsets)
    	: 
	m_velX(velX),
      	m_velY(velY),
      	m_r(r),
      	m_total(total),
      	m_rotation(rotation),
      	m_offsets(offsets),
      	m_shouldBeDeleted(false),
      	m_averageOffset(0)
{
    	// We set the point count to the random number
    	m_shape.setPointCount(m_total);

    	// Set the position for each of it's vertices
    	for (unsigned int i = 0; i < m_total; ++i) 
	{
        	// An angle mapped from i in range 0, m_total, to 0, 2 * pi
        	float angle = Utils::mapNumber(static_cast<float>(i), 0.f, static_cast<float>(m_total), 0.f, 6.28f);
        	// We add the offset that was randomly choosen to this vertice
        	float r = m_r + m_offsets.at(i);
        	m_averageOffset += m_offsets.at(i);
        	// We get the polar coordinates
        	float pX = r * cos(angle);
        	float pY = r * sin(angle);
        	// Finally we set the point and it's coordinates
        	m_shape.setPoint(i, sf::Vector2f(pX, pY));
    	}

	m_averageOffset /= m_offsets.size();

    	m_shape.setPosition(x, y);
    	m_shape.setOutlineColor(sf::Color::White);
    	m_shape.setOutlineThickness(2);
    	m_shape.setFillColor(sf::Color::Transparent);
}

void Asteroid::update(float deltaTime) 
{
	float x = m_shape.getPosition().x;
    	float y = m_shape.getPosition().y;

    	x += m_velX * deltaTime;
    	y += m_velY * deltaTime;

    	m_shape.rotate(m_rotation * deltaTime);

    	if (x > Utils::WIDTH)
       		x = 0;
    	else if (x < 0)
        	x = Utils::WIDTH;

    	if (y > Utils::HEIGHT)
        	y = 0;
    	else if (y < 0)
        	y = Utils::HEIGHT;

    	m_shape.setPosition(x, y);
}

void Asteroid::draw(sf::RenderWindow& window) 
{
    	window.draw(m_shape);
}

void Asteroid::setToDelete(bool b) 
{
    	m_shouldBeDeleted = b;
}

bool Asteroid::shouldDelete() 
{
	return m_shouldBeDeleted;
}

float Asteroid::getX() 
{
	return m_shape.getPosition().x;
}

float Asteroid::getY() 
{
	return m_shape.getPosition().y;
}

float Asteroid::getR() 
{
	return m_r;
}

float Asteroid::getAverageOffset() 
{
	return m_averageOffset;
}
