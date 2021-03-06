#pragma once
#include <SFML/Graphics.hpp>
#include "Assets.h"

/// <summary>
/// Responsible for storing statistical data
/// </summary>
class StatisticsBar {
public:
	// Constructor
	StatisticsBar();

	// Accessors
	/// <summary>
	/// Called in the GameLogic class to find out what level the player is on 
	/// </summary>
	/// <returns>
	/// Returns the game level
	/// </returns>
	/// <seealso cref = "GameLogic"/>
	[[nodiscard]] inline int GetLevel() { return m_Level; }
	/// <summary>
	/// Called in the GameLogic class to find out the number of gifts collected 
	/// </summary>
	/// <returns>
	/// Returns the game score
	/// </returns>
	/// <seealso cref = "GameLogic"/>
	[[nodiscard]] inline int GetScore() { return m_Score; }
	/// <summary>
	/// Called in the GameLogic class to monitor health points 
	/// </summary>
	/// <returns>
	/// Returns health points
	/// </returns>
	/// <seealso cref = "GameLogic"/>
	[[nodiscard]] inline int GetHealthPoints() { return m_HealthPoints; }

	// Modifiers
	/// <summary>
	/// Sets data to text
	/// </summary>
	/// <returns>
	/// Nothing
	/// </returns>
	void SetValues();
	/// <summary>
	/// Sets the position of elements
	/// </summary>
	/// <returns>
	/// Nothing
	/// </returns>
	void SetPositions(float windowPositionX, float windowPositionY);

	// Public methods
	/// <summary>
	/// Statistics bar update
	/// </summary>
	/// <returns>
	/// Nothing
	/// </returns>
	void Update();
	/// <summary>
	/// Called in the GameRender class to render the statistics bar
	/// </summary>
	/// <returns>
	///  Nothing
	/// </returns>
	/// <seealso cref = "GameRender"/>
	void Draw(sf::RenderWindow& window);
	/// <summary>
	/// Increases the number of collected gifts (score) 
	/// </summary>
	/// <returns>
	/// Nothing
	/// </returns>
	void ScoreUp();
	/// <summary>
	/// Reducing health points when the gift was not caught
	/// </summary>
	/// <returns>
	/// Nothing
	/// </returns>
	void ReduceHealthPoints();
	/// <summary>
	/// Resets statistics before starting a new game
	/// </summary>
	/// <returns>
	/// Nothing
	/// </returns>
	void NewGame();

private:
	// Member data
	int m_Level, m_Score, m_HealthPoints;
	sf::Text	 m_TextScore;
	sf::Text	 m_TextLevel;
	sf::Text	 m_TextHealthPoints;
}; // class StatisticsBar

StatisticsBar::StatisticsBar() : m_Level(1), m_Score(0), m_HealthPoints(3) {

	m_TextScore.setFont(Assets::Instance().GetFontLemon());
	m_TextLevel.setFont(Assets::Instance().GetFontLemon());
	m_TextHealthPoints.setFont(Assets::Instance().GetFontLemon());

	m_TextScore.setCharacterSize(50);
	m_TextLevel.setCharacterSize(50);
	m_TextHealthPoints.setCharacterSize(50);

	m_TextScore.setFillColor(sf::Color::White);
	m_TextLevel.setFillColor(sf::Color::White);
	m_TextHealthPoints.setFillColor(sf::Color::White);

}

void StatisticsBar::ScoreUp() {
	m_Score++;
	m_TextScore.setString("Score:" + std::to_string(m_Score));
}

void StatisticsBar::ReduceHealthPoints() {
	m_HealthPoints--;
	m_TextHealthPoints.setString("HP:" + std::to_string(m_HealthPoints));
}

void StatisticsBar::NewGame() {
	m_Level = 1;
	m_Score = 0;
	m_HealthPoints = 3;
}

void StatisticsBar::SetValues() {
	m_TextScore.setString("Score:" + std::to_string(m_Score));
	m_TextLevel.setString("Level:" + std::to_string(m_Level));
	m_TextHealthPoints.setString("HP:" + std::to_string(m_HealthPoints));
}

void StatisticsBar::SetPositions(float windowPositionX, float windowPositionY) {
	m_TextScore.setPosition(windowPositionX, windowPositionY - 240);
	m_TextLevel.setPosition(windowPositionX, windowPositionY - 180);
	m_TextHealthPoints.setPosition(windowPositionX, windowPositionY - 120);
}

void StatisticsBar::Update() {
	m_Level = m_Score / 10 + 1;
	m_TextLevel.setString("Level:" + std::to_string(m_Level));
}

void StatisticsBar::Draw(sf::RenderWindow& window) {
	window.draw(m_TextScore);
	window.draw(m_TextLevel);
	window.draw(m_TextHealthPoints);
}
