#pragma once
#include <SFML/Graphics.hpp>

class Gift {
public:
	// Constructor
	Gift() { }

	// Accessors
	[[nodiscard]] inline sf::FloatRect GetGlobalBounds() { return m_GiftSprite.getGlobalBounds(); }
	[[nodiscard]] inline sf::Sprite GetGiftSprite() { return m_GiftSprite; }

	// Modifiers
	void SetTexture(sf::Texture& texture);
	void SetPosition(float windowSizeX);

	// Public methods
	void Draw(sf::RenderWindow& window);
	void MoveGift(int level);
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