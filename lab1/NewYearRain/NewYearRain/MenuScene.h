#pragma once
#include <SFML/Graphics.hpp>

class MenuScene {

public:
	// Constructor
	MenuScene();

	// Accessors
	[[nodiscard]] inline bool GetScene() { return m_MenuScene; }

	// Modifiers
	void SetValuesAndPositions(int result, float windowPositionX, float windowPositionY);
	void SetScene();

	// Public methods
	bool Input(sf::RenderWindow& renderWindow);
	void Update(float dt);
	void Draw(sf::RenderWindow& window);

private:
	// Member data
	unsigned int m_BestResult;
	bool		 m_MenuScene;
	sf::Font	 m_Font;
	sf::Text	 m_TextNewGame;
	sf::Text	 m_TextQuit;
	sf::Text	 m_TextResult;
	sf::Text	 m_TextBestResult;
}; // class MenuScene

MenuScene::MenuScene() : m_MenuScene(0), m_BestResult(0) {
	m_Font.loadFromFile("C:\\dev\\lab3\\fonts\\20170.ttf");

	m_TextNewGame.setFont(m_Font);
	m_TextQuit.setFont(m_Font);
	m_TextResult.setFont(m_Font);
	m_TextBestResult.setFont(m_Font);

	m_TextNewGame.setCharacterSize(71);
	m_TextQuit.setCharacterSize(71);
	m_TextResult.setCharacterSize(71);
	m_TextBestResult.setCharacterSize(71);

}

void MenuScene::SetValuesAndPositions(int result, float windowPositionX, float windowPositionY) {
	int bestResult;
	std::ifstream file1;
	file1.open("bestResult.txt");
	file1 >> bestResult;
	file1.close();

	m_TextNewGame.setString("NEW GAME");
	m_TextQuit.setString("QUIT");
	m_TextResult.setString("Your result: " + std::to_string(result));
	m_TextBestResult.setString("Best result: " + std::to_string(bestResult));

	m_TextNewGame.setPosition(windowPositionX - 365, windowPositionY + 10);
	m_TextQuit.setPosition(windowPositionX - 235, windowPositionY + 100);
	m_TextResult.setPosition(windowPositionX - 300, windowPositionY - 85);
	m_TextBestResult.setPosition(windowPositionX - 300, windowPositionY - 150);
}

void MenuScene::SetScene() {
	m_MenuScene = 1;
}

bool MenuScene::Input(sf::RenderWindow& renderWindow) {
	if (sf::IntRect(renderWindow.getPosition().x - 365, renderWindow.getPosition().y + 10, 450, 80).contains(sf::Mouse::getPosition(renderWindow)))
		m_TextNewGame.setFillColor(sf::Color::Red);
	if (sf::IntRect(renderWindow.getPosition().x - 235, renderWindow.getPosition().y + 100, 175, 80).contains(sf::Mouse::getPosition(renderWindow)))
		m_TextQuit.setFillColor(sf::Color::Red);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && sf::IntRect(renderWindow.getPosition().x - 235, renderWindow.getPosition().y + 100, 175, 80).contains(sf::Mouse::getPosition(renderWindow))) //Пользователь нажал на QUIT
		renderWindow.close();
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
		sf::IntRect(renderWindow.getPosition().x - 365, renderWindow.getPosition().y + 10, 450, 80).contains(sf::Mouse::getPosition(renderWindow))) {
		m_MenuScene = 0;
		return 1;
	}
	return 0;
}

void MenuScene::Update(float dt) {
	m_TextNewGame.setFillColor(sf::Color::White);
	m_TextQuit.setFillColor(sf::Color::White);
}

void MenuScene::Draw(sf::RenderWindow& window) {
	if (m_MenuScene) {
		window.draw(m_TextNewGame);
		window.draw(m_TextQuit);
		window.draw(m_TextResult);
		window.draw(m_TextBestResult);
	}
}
