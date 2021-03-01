#pragma once
#include <SFML/Graphics.hpp>
#include "Assets.h"

class MenuScene {

public:
	// Constructor
	MenuScene();

	// Accessors

	// Modifiers
	void SetValues(int result);
	void SetPositions(float windowPositionX, float windowPositionY);

	// Public methods
	bool Input(sf::RenderWindow& renderWindow);
	void Update();
	void Draw(sf::RenderWindow& window);

private:
	// Member data
	unsigned int m_BestResult;
	sf::Text	 m_TextNewGame;
	sf::Text	 m_TextQuit;
	sf::Text	 m_TextResult;
	sf::Text	 m_TextBestResult;
}; // class MenuScene

MenuScene::MenuScene() : m_BestResult(0) {

	m_TextNewGame.setFont(Assets::Instance().GetFontAllura());
	m_TextQuit.setFont(Assets::Instance().GetFontAllura());
	m_TextResult.setFont(Assets::Instance().GetFontAllura());
	m_TextBestResult.setFont(Assets::Instance().GetFontAllura());

	m_TextNewGame.setCharacterSize(71);
	m_TextQuit.setCharacterSize(71);
	m_TextResult.setCharacterSize(71);
	m_TextBestResult.setCharacterSize(71);

}

void MenuScene::SetValues(int result) {
	int bestResult;
	std::ifstream file1;
	file1.open("bestResult.txt");
	file1 >> bestResult;
	file1.close();

	m_TextNewGame.setString("NEW GAME");
	m_TextQuit.setString("QUIT");
	m_TextResult.setString("Your result: " + std::to_string(result));
	m_TextBestResult.setString("Best result: " + std::to_string(bestResult));

}

void MenuScene::SetPositions(float windowPositionX, float windowPositionY) {
	m_TextNewGame.setPosition(windowPositionX - 365, windowPositionY + 10);
	m_TextQuit.setPosition(windowPositionX - 235, windowPositionY + 100);
	m_TextResult.setPosition(windowPositionX - 300, windowPositionY - 85);
	m_TextBestResult.setPosition(windowPositionX - 300, windowPositionY - 150);
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
		return 1;
	}
	return 0;
}

void MenuScene::Update() {
	m_TextNewGame.setFillColor(sf::Color::White);
	m_TextQuit.setFillColor(sf::Color::White);
}

void MenuScene::Draw(sf::RenderWindow& window) {
		window.draw(m_TextNewGame);
		window.draw(m_TextQuit);
		window.draw(m_TextResult);
		window.draw(m_TextBestResult);
}
