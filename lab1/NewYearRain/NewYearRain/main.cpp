#include "Engine.h"

/// <summary>
/// Game New Year Rain
/// </summary>
int main()
{
	srand(time(0));

	GameLogic game;
	GameRender render(&game);
	Engine engine(&game, &render);
	engine.Run();
}