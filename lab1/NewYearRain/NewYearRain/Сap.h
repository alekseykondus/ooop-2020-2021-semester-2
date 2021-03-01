#pragma once
#include <SFML/Graphics.hpp>

class Cap {
public:
	// Constructor
	Cap() { }

	// Accessors
	[[nodiscard]] inline sf::FloatRect GetGlobalBounds() { return m_�apSprite.getGlobalBounds(); }
	[[nodiscard]] inline sf::Sprite& Get�apSprite() { return m_�apSprite; }

	// Modifiers

	// Public methods
	void Input(float windowSizeX);
	void Draw(sf::RenderWindow& window);

private:
	// Member data
	sf::Sprite m_�apSprite;
}; // class Cap

void Cap::Input(float windowSizeX) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		m_�apSprite.move(-0.5f, 0.0f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		m_�apSprite.move(0.5f, 0.0f);

	if (m_�apSprite.getPosition().x > windowSizeX - m_�apSprite.getGlobalBounds().height)
		m_�apSprite.setPosition(0, m_�apSprite.getPosition().y);
	if (m_�apSprite.getPosition().x < 0)
		m_�apSprite.setPosition(windowSizeX - m_�apSprite.getGlobalBounds().height, m_�apSprite.getPosition().y);
}