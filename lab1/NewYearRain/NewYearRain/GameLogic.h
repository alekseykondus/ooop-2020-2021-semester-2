#pragma once
#include <SFML/Audio.hpp>
#include <fstream>
#include "Ñap.h"
#include "Gift.h"
#include "StatisticsBar.h"
#include "MenuScene.h"

/// <summary>
/// Responsible for the logic of the program 
/// </summary>
class GameLogic
{
public:
    /// <summary>
    /// Responsible for the current scene 
    /// </summary>
    enum class Scene { _GameScene = 1, _MenuScene = 2 };
    /// <summary>
    /// Static variable window width 
    /// </summary>
    static const int WINDOW_WIDTH = 800;
    /// <summary>
    /// Static variable window height 
    /// </summary>
    static const int WINDOW_HEIGHT = 600;

    // Constructor
    GameLogic() { };

    // Accessors
    /// <summary>
    /// Used to check the end of the game 
    /// </summary>
    /// <returns>
	///  Returns 1 if the game is over and 0 if the game is in progress 
	/// </returns>
    [[nodiscard]] inline bool GetEndGame() { return m_EndGame; }

    /// <summary>
    /// Used to find out which scene the game is currently in
    /// </summary>
    /// <returns>
    ///  Returns the current scene 
    /// </returns>
    [[nodiscard]] inline Scene GetScene() { return m_Scene; }
    /// <summary>
    /// Needed for rendering 
    /// </summary>
    /// <returns>
    ///  Returns the cap 
    /// </returns>
    [[nodiscard]] inline Cap& GetCap() { return m_Cap; }
    /// <summary>
    /// Needed to add gifts to this vector 
    /// </summary>
    /// <returns>
    ///  Returns a vector of gifts
    /// </returns>
    [[nodiscard]] inline std::vector<Gift>& GetGifts() { return m_Gifts; }
    /// <summary>
    /// Used to draw gifts that are on the field  
    /// </summary>
    /// <returns>
    /// Returns a vector of gifts
    /// </returns>
    [[nodiscard]] inline std::vector<Gift>& GetFieldGifts() { return m_FieldGifts; }
    /// <summary>
    /// Used to draw statistics 
    /// </summary>
    /// <returns>
    /// Returns a statistics bar
    /// </returns>
    [[nodiscard]] inline StatisticsBar& GetStatisticsBar() { return m_StatisticsBar; }
    /// <summary>
    /// Used to draw menu 
    /// </summary>
    /// <returns>
    /// Returns a menu
    /// </returns>
    [[nodiscard]] inline MenuScene& GetMenuScene() { return m_MenuScene; }
    /// <summary>
    /// Used to play the melody "fail" (when the player has not caught the gift) 
    /// </summary>
    /// <returns>
    /// Returns the sound of failure 
    /// </returns>
    [[nodiscard]] inline sf::Sound& GetSoundFail() { return m_SoundFail; }
    /// <summary>
    /// Used to play the melody "end game" (when the player lost) 
    /// </summary>
    /// <returns>
    /// Returns a loss melody
    /// </returns>
    [[nodiscard]] inline sf::Sound& GetSoundEndGame() { return m_SoundEndGame; }


    // Public methods
    /// <summary>
    /// The main method of this class. This is where the logic of the game is implemented
    /// </summary>
    /// <returns>
    /// Nothing
    /// </returns>
	void LogicOfGameScene();
    /// <summary>
    /// Update (this is where GameLogic :: LogicOfGameScene () starts) 
    /// </summary>
    /// <returns>
    ///  Nothing
    /// </returns>
    /// See <see cref = "GameLogic.LogicOfGameScene()"/>
	void Update();
    /// <summary>
    /// Clears all data (resets to the start of the game)
    /// </summary>
    /// <returns>
    ///  Nothing
    /// </returns>
	void Start();

private:
    // Member data
	int               m_SpawnTime;
    bool              m_EndGame;
    Scene             m_Scene;
	Cap               m_Cap;
	std::vector<Gift> m_Gifts;
	std::vector<Gift> m_FieldGifts;
	StatisticsBar     m_StatisticsBar;
	MenuScene         m_MenuScene;
	sf::Sound         m_SoundFail;
	sf::Sound         m_SoundEndGame;
}; // class GameLogic

void GameLogic::Start() {

	m_SpawnTime = 15;
	m_EndGame = 0;
    m_Scene = Scene::_GameScene;
	//m_GameScene = 1;
	if (!m_FieldGifts.empty()) {
		m_StatisticsBar.NewGame();
		m_FieldGifts.clear();
	}
	m_StatisticsBar.SetValues();
}

void GameLogic::Update() {
    if (m_Scene == Scene::_GameScene)
        LogicOfGameScene();
    m_StatisticsBar.Update();
    m_MenuScene.Update();
}

void GameLogic::LogicOfGameScene() {
    if (!m_EndGame) {
        for (size_t i = 0; i < m_FieldGifts.size(); i++) {
            m_FieldGifts[i].MoveGift(m_StatisticsBar.GetLevel());

            if (m_FieldGifts[i].GiftAbroad(WINDOW_HEIGHT)) {
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

        if (m_SpawnTime >= 1500 / sqrt(m_StatisticsBar.GetLevel() * 2)) {
            int i = rand() % 6;
            m_Gifts[i].SetPosition(WINDOW_WIDTH);
            m_FieldGifts.push_back(m_Gifts[i]);
            m_SpawnTime = 0;
        }

        for (size_t i = 0; i < m_FieldGifts.size(); i++) {
            if (m_Cap.GetGlobalBounds().intersects(m_FieldGifts[i].GetGlobalBounds())) {
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

        if (m_StatisticsBar.GetScore() > bestResult) {
            bestResult = m_StatisticsBar.GetScore();
            std::ofstream file2;
            file2.open("bestResult.txt");
            file2 << bestResult;
            file2.close();
        }
        m_Scene = Scene::_MenuScene;
        m_MenuScene.SetValues(m_StatisticsBar.GetScore());
    }
}
