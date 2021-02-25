#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

class StatisticsBar {
public:
	// Constructor
	StatisticsBar();

	// Accessors
	[[nodiscard]] inline int GetLevel() { return m_Level; }
	[[nodiscard]] inline int GetScore() { return m_Score; }
	[[nodiscard]] inline int GetHealthPoints() { return m_HealthPoints; }

	// Modifiers
	void SetValuesAndPositions(float windowPositionX, float windowPositionY);

	// Public methods
	void Update(float dt);
	void Draw(sf::RenderWindow& window);
	void ScoreUp();
	void ReduceHealthPoints();
	void NewGame();

private:
	// Member data
	int m_Level, m_Score, m_HealthPoints;
	sf::Font	 m_Font;
	sf::Text	 m_TextScore;
	sf::Text	 m_TextLevel;
	sf::Text	 m_TextHealthPoints;
}; // class StatisticsBar

StatisticsBar::StatisticsBar() : m_Level(1), m_Score(0), m_HealthPoints(3) {

	m_Font.loadFromFile("C:\\dev\\lab3\\fonts\\19919.ttf");
	m_TextScore.setFont(m_Font);
	m_TextLevel.setFont(m_Font);
	m_TextHealthPoints.setFont(m_Font);

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

void StatisticsBar::SetValuesAndPositions(float windowPositionX, float windowPositionY) {

	m_TextScore.setString("Score:" + std::to_string(m_Score));
	m_TextScore.setPosition(windowPositionX, windowPositionY - 240);

	m_TextLevel.setString("Level:" + std::to_string(m_Level));
	m_TextLevel.setPosition(windowPositionX, windowPositionY - 180);

	m_TextHealthPoints.setString("HP:" + std::to_string(m_HealthPoints));
	m_TextHealthPoints.setPosition(windowPositionX, windowPositionY - 120);
}

void StatisticsBar::Update(float dt) {
	m_Level = m_Score / 10 + 1;
	m_TextLevel.setString("Level:" + std::to_string(m_Level));
}

void StatisticsBar::Draw(sf::RenderWindow& window) {
	window.draw(m_TextScore);
	window.draw(m_TextLevel);
	window.draw(m_TextHealthPoints);
}
