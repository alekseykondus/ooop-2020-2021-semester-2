#pragma once
#include <SFML/Graphics.hpp>

/// <summary>
/// Stores the game header sprite for collecting gifts and methods for working with it
/// </summary>
class Cap {
public:
	// Constructor
	Cap() { }

	// Accessors
	/// <summary>
	/// Returns the dimensions of the sprite 
	/// </summary>
	/// <returns>
	///  Global bounds of cap 
	/// </returns>
	[[nodiscard]] inline sf::FloatRect GetGlobalBounds() { return m_�apSprite.getGlobalBounds(); }

	/// <summary>
	/// Returns the sprite cap 
	/// </summary>
	/// <returns>
	///  Sprite cap 
	/// </returns>
	[[nodiscard]] inline sf::Sprite& GetCapSprite() { return m_�apSprite; }

	// Public methods
	/// <summary>
	/// Handles pressing the Left Right keys (event handling)
	/// </summary>
	/// <returns>
	///  Nothing
	/// </returns>
	void Input(float windowSizeX);

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