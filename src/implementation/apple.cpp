#include "../headers/apple.h"

Apple::Apple()
{
	this -> tApple.loadFromFile("static/assets/apple.png");
	this -> setTexture(tApple);
	this -> setScale((float)sqW / this -> tApple.getSize().x, (float)sqW / this -> tApple.getSize().y);
}

int* Apple::iGetRect()
{
	this -> iRect[0] = this -> iX();
	this -> iRect[1] = this -> iY();
	return this -> iRect;
}

void Apple::setRandomPos(Snake* snake, Map* map)
{
	while (true)
	{
		int iRX = rand() % map -> iCols * sqW;
		if (iRX == 0) iRX = shrubW + sqW;
		else if (iRX == sqW) iRX = shrubW;
		else if (iRX == wW - sqW) iRX -= sqW + shrubW;
		else if (iRX == wW - shrubW) iRX -= sqW;
		int iRY = rand() % map -> iRows * sqW;
		if (iRY == 0) iRY = sqW + shrubW;
		else if (iRY == sqW) iRY = shrubW;
		else if (iRY == wH - sqW) iRY -= sqW + shrubW;
		else if (iRY == wH - shrubW) iRY -= sqW;
		bool bCollide = false;
		for (int i = 0; i < snake -> iTailLen; ++i)
		{
			int iRect1[4]{iRX, iRY, sqW, sqW};
			int iRect2[4]{(int)snake -> tail[i] -> getPosition().x, (int)snake -> tail[i] -> getPosition().y, sqW, sqW};
			if (bCollideRect(iRect1, iRect2)) bCollide = true;
		}
		if (!bCollide)
		{
			this -> setPosition(iRX, iRY);
			break;
		}
	}
}