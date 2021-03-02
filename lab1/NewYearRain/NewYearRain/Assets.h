#pragma once
#include <SFML/Graphics.hpp>

/// <summary>
/// Responsible for loading game resources 
/// </summary>
class Assets {
public:
	// Constructor
	Assets() { };

	// Accessors
	[[nodiscard]] inline sf::Font& GetFontLemon() { return m_FontLemon; }
	[[nodiscard]] inline sf::Font& GetFontAllura() { return m_FontAllura; }
	[[nodiscard]] inline sf::Texture& GetBackgroundTexture() { return m_BackgroundTexture; }
	[[nodiscard]] inline sf::Texture& GetCapTexture() { return m_ÑapTexture; }
	[[nodiscard]] inline sf::Texture& GetEndGameTexture() { return m_EndGameTexture; }
	[[nodiscard]] inline std::vector <sf::Texture>& GetGiftsTexture() { return m_GiftsTexture; }
	[[nodiscard]] inline sf::SoundBuffer& GetSoundBufferFail() { return m_SoundBufferFail; }
	[[nodiscard]] inline sf::SoundBuffer& GetSoundBufferEndGame() { return m_SoundBufferEndGame; }

	// Public methods
	/// <summary>
	/// Creates a static variable Assets 
	/// </summary>
	/// <returns>
	/// Returns the static variable Assets
	/// </returns>
	static Assets& Instance() {
		static Assets r;
		return r;
	}
	/// <summary>
	/// Method loads fonts, sounds, textures
	/// </summary>
	/// <returns>
	/// Nothing
	/// </returns>
	void Load();

private:
	// Member data
	sf::Font		 m_FontLemon;
	sf::Font		 m_FontAllura;
	sf::Texture      m_BackgroundTexture;
	sf::Texture      m_ÑapTexture;
	sf::Texture      m_EndGameTexture;
	std::vector <sf::Texture> m_GiftsTexture;
	sf::SoundBuffer  m_SoundBufferFail;
	sf::SoundBuffer  m_SoundBufferEndGame;
}; // class Assets

void Assets::Load() {
	m_GiftsTexture.resize(6);

	m_FontAllura.loadFromFile("fonts\\Allura.ttf");
	m_FontLemon.loadFromFile("fonts\\Lemon.ttf");

	m_GiftsTexture[0].loadFromFile("images\\p0.png");
	m_GiftsTexture[1].loadFromFile("images\\p1.png");
	m_GiftsTexture[2].loadFromFile("images\\p2.png");
	m_GiftsTexture[3].loadFromFile("images\\p3.png");
	m_GiftsTexture[4].loadFromFile("images\\p4.png");
	m_GiftsTexture[5].loadFromFile("images\\p5.png");

	m_SoundBufferFail.loadFromFile("music\\Fail.ogg");
	m_SoundBufferEndGame.loadFromFile("music\\EndGame.ogg");

	m_BackgroundTexture.loadFromFile("images\\Background.png");
	m_ÑapTexture.loadFromFile("images\\Cap.png");
	//    m_GiftsTexture.loadFromFile("images\\Gifts.png");
	m_EndGameTexture.loadFromFile("images\\EndGame.png");
}