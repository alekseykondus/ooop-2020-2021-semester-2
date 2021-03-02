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
	[[nodiscard]] inline sf::FloatRect GetGlobalBounds() { return m_ÑapSprite.getGlobalBounds(); }

	/// <summary>
	/// Returns the sprite cap 
	/// </summary>
	/// <returns>
	///  Sprite cap 
	/// </returns>
	[[nodiscard]] inline sf::Sprite& GetCapSprite() { return m_ÑapSprite; }

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