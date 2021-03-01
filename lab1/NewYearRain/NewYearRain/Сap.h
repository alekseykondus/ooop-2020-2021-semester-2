#pragma once
#include <SFML/Graphics.hpp>

class Cap {
public:
	// Constructor
	Cap() { }

	// Accessors
	[[nodiscard]] inline sf::FloatRect GetGlobalBounds() { return m_ÑapSprite.getGlobalBounds(); }
	[[nodiscard]] inline sf::Sprite& GetÑapSprite() { return m_ÑapSprite; }

	// Modifiers

	// Public methods
	void Input(float windowSizeX);
	void Draw(sf::RenderWindow& window);

private:
	// Member data
	sf::Sprite m_ÑapSprite;
}; // class Cap

void Cap::Input(float windowSizeX) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		m_ÑapSprite.move(-0.5f, 0.0f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		m_ÑapSprite.move(0.5f, 0.0f);

	if (m_ÑapSprite.getPosition().x > windowSizeX - m_ÑapSprite.getGlobalBounds().height)
		m_ÑapSprite.setPosition(0, m_ÑapSprite.getPosition().y);
	if (m_ÑapSprite.getPosition().x < 0)
		m_ÑapSprite.setPosition(windowSizeX - m_ÑapSprite.getGlobalBounds().height, m_ÑapSprite.getPosition().y);
}