#include "../headers/config.h"
#include "snake.h"
#include "map.h"

class Apple : public Sprite
{
	public:
		int iRect[4]{0, 0, sqW, sqW};
		Texture tApple;

		Apple();

		int iX()
		{
			return this -> getPosition().x;
		}
		int iY()
		{
			return this -> getPosition().y;
		}
		int* iGetRect();

		void setRandomPos(Snake* snake, Map* map);
};