#pragma once
#include <SFML/Graphics.hpp>
#include "GameLogic.h"

class GameRender
{
public:
    // Constructor
	GameRender(GameLogic* gameLogic);

    // Accessors
    sf::RenderWindow& GetRenderWindow() { return m_RenderWindow; }

    // Modifiers

    // Public methods
    void TimeDelay(int x);
	void Draw();

private:
    GameLogic* m_GameLogic;
    sf::RenderWindow m_RenderWindow;

    sf::Sprite       m_BackgroundSprite;
    sf::Sprite       m_EndGameSprite;
};

GameRender::GameRender(GameLogic* gameLogic) : m_GameLogic(gameLogic) {
    m_RenderWindow.create(sf::VideoMode(m_GameLogic->WINDOW_WIDTH, m_GameLogic->WINDOW_HEIGHT), "NewYearRain!", sf::Style::Close | sf::Style::Titlebar);
    Assets::Instance().Load();

    Gift gift0, gift1, gift2, gift3, gift4, gift5;
    gift0.SetTexture(Assets::Instance().GetGiftsTexture()[0]);
    gift1.SetTexture(Assets::Instance().GetGiftsTexture()[1]);
    gift2.SetTexture(Assets::Instance().GetGiftsTexture()[2]);
    gift3.SetTexture(Assets::Instance().GetGiftsTexture()[3]);
    gift4.SetTexture(Assets::Instance().GetGiftsTexture()[4]);
    gift5.SetTexture(Assets::Instance().GetGiftsTexture()[5]);
    m_GameLogic->GetGifts().push_back(gift0);
    m_GameLogic->GetGifts().push_back(gift1);
    m_GameLogic->GetGifts().push_back(gift2);
    m_GameLogic->GetGifts().push_back(gift3);
    m_GameLogic->GetGifts().push_back(gift4);
    m_GameLogic->GetGifts().push_back(gift5);

    m_GameLogic->GetSoundFail().setBuffer(Assets::Instance().GetSoundBufferFail());
    m_GameLogic->GetSoundEndGame().setBuffer(Assets::Instance().GetSoundBufferEndGame());


    m_BackgroundSprite.setTexture(Assets::Instance().GetBackgroundTexture());
    m_EndGameSprite.setTexture(Assets::Instance().GetEndGameTexture());
    m_EndGameSprite.setPosition(m_RenderWindow.getPosition().x * 0.5f, m_RenderWindow.getPosition().y * 0.5f + 100);

    m_GameLogic->GetCap().GetÑapSprite().setTexture(Assets::Instance().GetÑapTexture());
    m_GameLogic->GetCap().GetÑapSprite().setPosition(400, m_RenderWindow.getSize().y - m_GameLogic->GetCap().GetÑapSprite().getGlobalBounds().height);

    m_GameLogic->GetStatisticsBar().SetPositions(m_RenderWindow.getPosition().x, m_RenderWindow.getPosition().y);
    m_GameLogic->GetMenuScene().SetPositions(m_RenderWindow.getPosition().x, m_RenderWindow.getPosition().y);
}

void GameRender::Draw() {
    m_RenderWindow.clear();
    m_RenderWindow.draw(m_BackgroundSprite);

    if (m_GameLogic->GetScene() == GameLogic::Scene::_GameScene) {
        m_RenderWindow.draw(m_GameLogic->GetCap().GetÑapSprite());
        for (auto& gift : m_GameLogic->GetFieldGifts())
            m_RenderWindow.draw(gift.GetGiftSprite());
        m_GameLogic->GetStatisticsBar().Draw(m_RenderWindow);

        if (m_GameLogic->GetEndGame())
            m_RenderWindow.draw(m_EndGameSprite);
    }
    else if (m_GameLogic->GetScene() == GameLogic::Scene::_MenuScene)
        m_GameLogic->GetMenuScene().Draw(m_RenderWindow);
    m_RenderWindow.display();

    if (m_GameLogic->GetEndGame() && m_GameLogic->GetScene() == GameLogic::Scene::_GameScene)
        TimeDelay(1);
}

static float ftime = 0;
void GameRender::TimeDelay(int x) {
    sf::Clock clock;
    while (ftime < x)
        ftime = clock.getElapsedTime().asSeconds();
    ftime = 0;
}
