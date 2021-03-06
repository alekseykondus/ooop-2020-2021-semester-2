#pragma once
#include <fstream>
#include "GameRender.h"

/// <summary>
/// Game engine
/// </summary>
class Engine
{
public:
    // Constructor
    /// <summary>
    /// Engine class constructor, accepts a GameLogic pointer and a GameRender pointer 
    /// </summary>
    /// See <see cref = "GameLogic"/>
    /// <seealso cref = "GameRender"/>
    Engine(GameLogic* gameLogic, GameRender* gameRender);

    // Public methods
    /// <summary>
    /// Method launches the game
    /// </summary>
    /// <returns>
    /// Nothing
    /// </returns>
    void Run();

private:
    // Member data
    GameLogic*       m_GameLogic;
    GameRender*      m_GameRender;
    sf::Event        m_Event;

    // Private methods
    void TimeDelay(int x);
    void Input();
    void Update();
}; // class Engine

Engine::Engine(GameLogic* gameLogic, GameRender* gameRender) : m_GameLogic(gameLogic), m_GameRender(gameRender) { }

void Engine::Run() {

    m_GameLogic->Start();

    while (m_GameRender->GetRenderWindow().isOpen()) {

        m_GameLogic->Update();
        Input();
        m_GameRender->Draw();
    }
}

void Engine::Input() {
   while (m_GameRender->GetRenderWindow().pollEvent(m_Event)) {
        if (m_Event.type == sf::Event::Closed) // ������������ ����� �� �������� 
            m_GameRender->GetRenderWindow().close();
        if (m_Event.type == sf::Event::KeyPressed && m_Event.key.code == sf::Keyboard::Escape) // ������������ ����� �� �Esc� 
            m_GameRender->GetRenderWindow().close();
   }

   if (m_GameLogic->GetScene() == GameLogic::Scene::_GameScene)
       m_GameLogic->GetCap().Input(m_GameRender->GetRenderWindow().getSize().x);
   else
       if (m_GameLogic->GetMenuScene().Input(m_GameRender->GetRenderWindow()))
           Run();
}