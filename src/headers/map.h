#include "../headers/config.h"

#ifndef MAP_OBJ
	#define MAP_OBJ
	class Map : public RenderWindow
	{
		public:
			int iCols = wW / sqW;
			int iRows = wH / sqW;
			
			Map(int FPS);

			void load();
			void drawBackground();
			void drawWalls();
			void drawScore(int iScore, int iMaxScore);
			void showGameOver(int iScore);

		private:
			Color textColor = Color(65, 65, 65);

			Text gameOverText;
			Text scoreText;
			Text clickEnterToReturnText;
			Text score;
			Text maxScore;

			Texture tGround;
			Texture tShrub[3];
			
			Sprite sGround;
			Sprite sShrub[3];
			
			Font Roboto_Light_Font;

	};
#endif