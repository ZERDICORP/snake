#include "./headers/config.h"
#include "./headers/game.h"
#include "./headers/map.h"
#include "./headers/snake.h"
#include "./headers/apple.h"

int main()
{
	srand(time(NULL));
	Game game(60);
	Map map(game.FPS);
	Snake snake;
	Apple apple;
	apple.setPosition(wW / 2, wH / 2);
	apple.setRandomPos(&snake, &map);
	while (map.isOpen()) // ← [-main cycle-]
	{
		Event event; // ← [-even object-]
		while (map.pollEvent(event)) // ← [-even filter-]
		{
			if (event.type == Event::Closed) // ← [-pressing the window close button-]
				map.close(); // ← [-close window-]
			if (event.type == Event::KeyPressed) // ← [-pressing any key on keyboard-]
			{
				if (event.key.code == Keyboard::Escape) // ← [-if key - ESC-]
					map.close(); // ← [-close window-]
				if (event.key.code == Keyboard::Enter)
				{
					if (game.bGameOver)
					{
						snake.initTail();
						apple.setRandomPos(&snake, &map);
						game.toggleGameOver();
					}
				}
			}
		}
		map.drawBackground();
		game.iScore = snake.iTailLen - snake.iTailLenDefault;
		if (!game.bGameOver)
		{
			if (game.iScore > game.iMaxScore) game.iMaxScore = game.iScore;
			map.drawScore(game.iScore, game.iMaxScore);
			if (!snake.bTurn) snake.movement();
			map.draw(apple);
			if (game.iGetDelayCount() == game.iGetDelay())
			{
				snake.moveTail();
				game.setDelayCount(0);
				if (snake.bTurn) snake.bTurn = false;
			}
			game.setDelayCount(game.iGetDelayCount() + 1);
			for (int i = 0; i < snake.iTailLen; ++i)
				map.draw(*snake.tail[i]);
			game.setGameOver(snake.bCollideWalls());
			int iTailItemIndex = snake.iTouchedTail();
			if (iTailItemIndex) snake.spliceTail(iTailItemIndex);
			if (bCollideRect(snake.iGetHeadRect(), apple.iGetRect()))
			{
				snake.addTailItem();
				apple.setRandomPos(&snake, &map);
			}
		}
		else
			map.showGameOver(game.iScore);
		map.drawWalls();
		map.display();
	}
	return 0;
}