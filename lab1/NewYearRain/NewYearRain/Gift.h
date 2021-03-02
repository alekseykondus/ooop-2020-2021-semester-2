#pragma once
#include <SFML/Graphics.hpp>

/// <summary>
/// Stores the gift sprite and methods for working with it
/// </summary>
class Gift {
public:
	// Constructor
	Gift() { }

	// Accessors
	/// <summary>
	/// Returns the dimensions of the sprite 
	/// </summary>
	/// <returns>
	/// Global bounds of gift 
	/// </returns>
	[[nodiscard]] inline sf::FloatRect GetGlobalBounds() { return m_GiftSprite.getGlobalBounds(); }
	/// <summary>
	/// Returns the sprite gift 
	/// </summary>
	/// <returns>
	///  Sprite gift 
	/// </returns>
	[[nodiscard]] inline sf::Sprite GetGiftSprite() { return m_GiftSprite; }

	// Modifiers
	/// <summary>
	/// Sets the texture of the sprite's gift
	/// </summary>
	/// <returns>
	/// Nothing
	/// </returns>
	void SetTexture(sf::Texture& texture);
	/// <summary>
	/// Sets the position of the gift sprite 
	/// </summary>
	/// <returns>
	/// Nothing
	/// </returns>
	void SetPosition(float windowSizeX);

	// Public methods
	/// <summary>
	/// Gift movement (gift falls down)
	/// </summary>
	/// <returns>
	/// Nothing
	/// </returns>
	void MoveGift(int level);
	/// <summary>
	/// Needed to control whether the gift has gone beyond the window 
	/// </summary>
	/// <returns>
	/// Returns 1 if the gift is out of bounds
	/// </returns>
	bool GiftAbroad(float windowSizeY);

private:
	// Member data
	sf::Sprite m_GiftSprite;
}; // class Gift

void Gift::SetTexture(sf::Texture& texture) {
	m_GiftSprite.setTexture(texture);
}

void Gift::SetPosition(float windowSizeX) {
	m_GiftSprite.setPosition(rand() % int(windowSizeX - m_GiftSprite.getGlobalBounds().height), 0);
}

void Gift::MoveGift(int level) {
	m_GiftSprite.move(0.f, level / 10.f);
}

bool Gift::GiftAbroad(float windowSizeY) {
	return m_GiftSprite.getPosition().y + 10 > windowSizeY;
}