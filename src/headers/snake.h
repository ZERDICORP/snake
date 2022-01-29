#include "../headers/config.h"

#ifndef SNAKE_OBJ
	#define SNAKE_OBJ
		class Snake
		{
			public:
				RectangleShape** tail = new RectangleShape* [iTailLen];

				int iTailLenDefault = 2;
				int iTailLen = iTailLenDefault;

				bool bFirstTailInit = true;
				bool bTurn = false;

				Snake();

				int iHeadX()
				{
					return this -> tail[0] -> getPosition().x;
				}
				int iHeadY()
				{
					return this -> tail[0] -> getPosition().y;
				}
				int* iGetHeadRect();
				int iTouchedTail();

				void initTail();
				void moveTail();
				void addTailItem();
				void movement();
				void spliceTail(int iTailItemIndex);

				bool bCollideWalls();
				bool bBehindTheWalls();

			private:
				int iVector[2]{sqW, 0};
				int iRect[4]{0, 0, sqW, sqW};

				Texture tHead[4];
				Texture tBody[4];
				Texture tBodyWithCargo[4];
				Texture tBodyTurn[4];
				Texture tBodyTurnWithCargo[4];
				Texture tBodyTurnWithCrystal[4];
				Texture tEnd[4];
				Texture tBoom;

				Texture* textureByVector(Texture* textures, int iVX, int iVY);

				void load();
				void reset();
		};
#endif