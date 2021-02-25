#pragma once
#include <SFML/Audio.hpp>
#include <fstream>
#include "Ñap.h"
#include "Gift.h"
#include "StatisticsBar.h"
#include "MenuScene.h"

class Engine
{
public:
    // Constructor
    Engine();

    // Public methods
    void Start();

private:
    // Member data
    int  m_SpawnTime;
    bool m_EndGame, m_GameScene;

    sf::RenderWindow m_RenderWindow;
    sf::Event        m_Event;

    sf::Texture      m_BackgroundTexture;
    sf::Texture      m_ÑapTexture;
    sf::Texture      m_EndGameTexture;
    std::vector <sf::Texture> m_GiftsTexture;

    sf::Sprite       m_BackgroundSprite;
    sf::Sprite       m_EndGameSprite;

    sf::SoundBuffer  m_SoundBufferFail;
    sf::SoundBuffer  m_SoundBufferEndGame;
    sf::Sound        m_SoundFail;
    sf::Sound        m_SoundEndGame;

    Cap               m_Cap;
    std::vector<Gift> m_Gifts;
    std::vector<Gift> m_FieldGifts;
    StatisticsBar     m_StatisticsBar;
    MenuScene         m_MenuScene;

    // Private methods
    void LogicOfGameScene();
    void TimeDelay(int x);
    void Input();
    void Update(float dtAsSeconds);
    void Draw();
}; // class Engine

Engine::Engine() : m_EndGame(0), m_GameScene(1) {
    m_RenderWindow.create(sf::VideoMode(800, 600), "Game!", sf::Style::Close | sf::Style::Titlebar );
    srand(time(0));

    m_GiftsTexture.resize(6);
        
    m_GiftsTexture[0].loadFromFile("images\\p0.png");
    m_GiftsTexture[1].loadFromFile("images\\p1.png");
    m_GiftsTexture[2].loadFromFile("images\\p2.png");
    m_GiftsTexture[3].loadFromFile("images\\p3.png");
    m_GiftsTexture[4].loadFromFile("images\\p4.png");
    m_GiftsTexture[5].loadFromFile("images\\p5.png");

    Gift gift0, gift1, gift2, gift3, gift4, gift5;
    gift0.SetTexture(m_GiftsTexture[0]);
    gift1.SetTexture(m_GiftsTexture[1]);
    gift2.SetTexture(m_GiftsTexture[2]);
    gift3.SetTexture(m_GiftsTexture[3]);
    gift4.SetTexture(m_GiftsTexture[4]);
    gift5.SetTexture(m_GiftsTexture[5]);
    m_Gifts.push_back(gift0);
    m_Gifts.push_back(gift1);
    m_Gifts.push_back(gift2);
    m_Gifts.push_back(gift3);
    m_Gifts.push_back(gift4);
    m_Gifts.push_back(gift5);

    m_SoundBufferFail.loadFromFile("music\\Fail.ogg");
    m_SoundBufferEndGame.loadFromFile("music\\EndGame.ogg");

    m_SoundFail.setBuffer(m_SoundBufferFail);
    m_SoundEndGame.setBuffer(m_SoundBufferEndGame);

    m_BackgroundTexture.loadFromFile("images\\Background.png");
    m_ÑapTexture.loadFromFile("images\\Cap.png");
//    m_GiftsTexture.loadFromFile("images\\Gifts.png");
    m_EndGameTexture.loadFromFile("images\\EndGame.png");

    m_BackgroundSprite.setTexture(m_BackgroundTexture);
    m_EndGameSprite.setTexture(m_EndGameTexture);
    m_EndGameSprite.setPosition(m_RenderWindow.getPosition().x * 0.5f, m_RenderWindow.getPosition().y * 0.5f + 100);

    m_Cap.SetTextureAndPosition(m_ÑapTexture, m_RenderWindow.getSize().y);
}

void Engine::Start() {
    m_SpawnTime = 15;
    m_EndGame = 0;
    m_GameScene = 1;
    if (!m_FieldGifts.empty()) {
        m_StatisticsBar.NewGame();
        m_FieldGifts.clear();
    }

    m_StatisticsBar.SetValuesAndPositions(m_RenderWindow.getPosition().x, m_RenderWindow.getPosition().y);

    sf::Clock clock;

    while (m_RenderWindow.isOpen()) {
        sf::Time dt = clock.restart();

        float dtAsSeconds = dt.asSeconds();

        Update(dtAsSeconds);
        Input();
        Draw();
    }
}

void Engine::LogicOfGameScene() {
    if (!m_EndGame) {
        for (size_t i = 0; i < m_FieldGifts.size(); i++) {
            m_FieldGifts[i].MoveGift(m_StatisticsBar.GetLevel());

            if (m_FieldGifts[i].GiftAbroad(m_RenderWindow.getSize().y)) {
                m_FieldGifts.erase(m_FieldGifts.begin() + i);
                m_StatisticsBar.ReduceHealthPoints();
                if (m_StatisticsBar.GetHealthPoints())
                    m_SoundFail.play();
            }
            if (m_StatisticsBar.GetHealthPoints() == 0) {
                m_EndGame = 1;
                m_SoundEndGame.play();
            }
        }

        if (m_SpawnTime < 1500 / sqrt(m_StatisticsBar.GetLevel() * 2))
            m_SpawnTime++;

        if (m_SpawnTime >= 1500 / sqrt(m_StatisticsBar.GetLevel() * 2))
        {
            int i = rand() % 6;
            m_Gifts[i].SetPosition(m_RenderWindow.getSize().x);
            m_FieldGifts.push_back(m_Gifts[i]);
            m_SpawnTime = 0;
        }

        for (size_t i = 0; i < m_FieldGifts.size(); i++) {
            if (m_Cap.GetGlobalBounds().intersects(m_FieldGifts[i].GetGlobalBounds()))
            {
                m_StatisticsBar.ScoreUp();
                m_FieldGifts.erase(m_FieldGifts.begin() + i);
            }
        }
    }
    else {
        int bestResult;
        std::ifstream file1;
        file1.open("bestResult.txt");
        file1 >> bestResult;
        file1.close();

        if (m_StatisticsBar.GetScore() > bestResult)
        {
            bestResult = m_StatisticsBar.GetScore();
            std::ofstream file2;
            file2.open("bestResult.txt");
            file2 << bestResult;
            file2.close();
        }
        m_GameScene = 0;
        m_MenuScene.SetValuesAndPositions(m_StatisticsBar.GetScore(), m_RenderWindow.getPosition().x, m_RenderWindow.getPosition().y);
    }
}

static float ftime = 0;
void Engine::TimeDelay(int x) {
    sf::Clock clock;
    while (ftime < x)
        ftime = clock.getElapsedTime().asSeconds();
    ftime = 0;
}

void Engine::Input() {
   while (m_RenderWindow.pollEvent(m_Event)) {
        if (m_Event.type == sf::Event::Closed) // Ïîëüçîâàòåëü íàæàë íà «êðåñòèê» 
            m_RenderWindow.close();
        if (m_Event.type == sf::Event::KeyPressed && m_Event.key.code == sf::Keyboard::Escape) // Ïîëüçîâàòåëü íàæàë íà «Esc» 
            m_RenderWindow.close();
   }
   if (m_GameScene)
       m_Cap.Input(m_RenderWindow.getSize().x);
   else if (m_MenuScene.GetScene())
       if (m_MenuScene.Input(m_RenderWindow))
            Start();
}

void Engine::Update(float dtAsSeconds) {
    if (m_GameScene)
        LogicOfGameScene();

    m_StatisticsBar.Update(dtAsSeconds);
    m_MenuScene.Update(dtAsSeconds);
}

void Engine::Draw() {
    m_RenderWindow.clear();
    m_RenderWindow.draw(m_BackgroundSprite);

    if (m_GameScene) {
        m_Cap.Draw(m_RenderWindow);
        for (auto& gift : m_FieldGifts)
            gift.Draw(m_RenderWindow);
        m_StatisticsBar.Draw(m_RenderWindow);

        if (m_EndGame)
            m_RenderWindow.draw(m_EndGameSprite);
    }
    else if (m_MenuScene.GetScene())
        m_MenuScene.Draw(m_RenderWindow);
    m_RenderWindow.display();

    if (m_EndGame && !m_MenuScene.GetScene()) {
        TimeDelay(1);
        m_MenuScene.SetScene();
    }
}