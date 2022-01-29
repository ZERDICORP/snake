#include "../headers/snake.h"

Snake::Snake()
{
	this -> load();
	this -> initTail();
}

void Snake::load()
{
	for (int i = 0; i < 4; ++i)
		this -> tHead[i].loadFromFile("static/assets/tail/head/head" + to_string(i) + ".png");	

	for (int i = 0; i < 4; ++i)
		this -> tBody[i].loadFromFile("static/assets/tail/body/body" + to_string(i) + ".png");	

	for (int i = 0; i < 4; ++i)
		this -> tBodyWithCargo[i].loadFromFile("static/assets/tail/bodyWithCargo/body" + to_string(i) + ".png");
	
	for (int i = 0; i < 4; ++i)
		this -> tBodyTurn[i].loadFromFile("static/assets/tail/bodyTurn/body" + to_string(i) + ".png");

	for (int i = 0; i < 4; ++i)
		this -> tBodyTurnWithCargo[i].loadFromFile("static/assets/tail/bodyTurn/withCargo/body" + to_string(i) + ".png");
	
	for (int i = 0; i < 4; ++i)
		this -> tBodyTurnWithCrystal[i].loadFromFile("static/assets/tail/bodyTurn/withCrystal/body" + to_string(i) + ".png");

	for (int i = 0; i < 4; ++i)
		this -> tEnd[i].loadFromFile("static/assets/tail/end/end" + to_string(i) + ".png");
	
	this -> tBoom.loadFromFile("static/assets/tail/boom.png");
}

bool Snake::bBehindTheWalls()
{
	return (this -> iHeadX() >= 0 && this -> iHeadX() < wW) && (this -> iHeadY() >= 0 && this -> iHeadY() < wH);
}

Texture* Snake::textureByVector(Texture* textures, int iVX, int iVY)
{
	if (!iVX && iVY < 0)
		return &textures[0];
	if (!iVX && iVY > 0)
		return &textures[1];
	if (iVX < 0 && !iVY)
		return &textures[2];
	if (iVX > 0 && !iVY)
		return &textures[3];
	return &textures[0];
}

int iToUnit(int num)
{
	return num != 0 ? num / abs(num) : 0;
}

Texture* tGetTurnTextureByVectors(Texture* textures, int iDX1, int iDY1, int iDX2, int iDY2)
{
	// ↓ [-top-]
	if ((!iDX1 && iDY1 < 0) && (iDX2 < 0 && !iDY2))
		return &textures[0];
	if ((!iDX1 && iDY1 < 0) && (iDX2 > 0 && !iDY2))
		return &textures[1];
	// ↓ [-bottom-]
	if ((!iDX1 && iDY1 > 0) && (iDX2 < 0 && !iDY2))
		return &textures[2];
	if ((!iDX1 && iDY1 > 0) && (iDX2 > 0 && !iDY2))
		return &textures[3];
	// ↓ [-left-]
	if ((iDX1 < 0 && !iDY1) && (!iDX2 && iDY2 > 0))
		return &textures[1];
	if ((iDX1 < 0 && !iDY1) && (!iDX2 && iDY2 < 0))
		return &textures[3];
	// ↓ [-right-]
	if ((iDX1 > 0 && !iDY1) && (!iDX2 && iDY2 > 0))
		return &textures[0];
	if ((iDX1 > 0 && !iDY1) && (!iDX2 && iDY2 < 0))
		return &textures[2];
	return &textures[0];
}

void Snake::moveTail()
{
	int iLastX = this -> iHeadX(), iLastY =  this -> iHeadY();
	int iDX = this -> iVector[0], iDY = this -> iVector[1];
	for (int i = 1; i < this -> iTailLen; ++i)
	{
		int iTIX = this -> tail[i] -> getPosition().x, iTIY = this -> tail[i] -> getPosition().y;
		int iTX = iLastX - iTIX, iTY = iLastY - iTIY;
		if (iToUnit(iDX) != iToUnit(iTX) || iToUnit(iDY) != iToUnit(iTY))
		{
			if (iTX || iTY)
			{
				if (i < this -> iTailLenDefault - 1)
					this -> tail[i] -> setTexture(tGetTurnTextureByVectors(this -> tBodyTurn, iTX, iTY, iDX, iDY));
				else
				{
					if (i < this -> iTailLen - 1)
						this -> tail[i] -> setTexture(tGetTurnTextureByVectors(this -> tBodyTurnWithCargo, iTX, iTY, iDX, iDY));
					if (i == this -> iTailLen - 1)
						this -> tail[i] -> setTexture(tGetTurnTextureByVectors(this -> tBodyTurnWithCrystal, iTX, iTY, iDX, iDY));
				}
			}
		}
		else
		{
			if (i < this -> iTailLen - 1)
			{
				if (i < this -> iTailLenDefault - 1)
				{
					this -> tail[i] -> setTexture(this -> textureByVector(this -> tBody, iTX, iTY));
				}
				else
					this -> tail[i] -> setTexture(this -> textureByVector(this -> tBodyWithCargo, iTX, iTY));
			}
			else if (i == this -> iTailLen - 1)
				if (iTX || iTY)
					this -> tail[i] -> setTexture(this -> textureByVector(this -> tEnd, iTX, iTY));
		}
		this -> tail[i] -> setPosition(iLastX, iLastY);
		iDX = iTX, iDY = iTY;
		iLastX = iTIX, iLastY = iTIY;
	}
	this -> tail[0] -> move(this -> iVector[0], this -> iVector[1]);
	this -> tail[0] -> setTexture(this -> textureByVector(this -> tHead, this -> iVector[0], this -> iVector[1]));
}

int* Snake::iGetHeadRect()
{
	this -> iRect[0] = this -> iHeadX();
	this -> iRect[1] = this -> iHeadY();
	return this -> iRect;
}

void Snake::reset()
{
	this -> iTailLen = this -> iTailLenDefault;
	delete[] this -> tail;
	this -> tail = new RectangleShape* [this -> iTailLen];
	this -> iVector[0] = sqW;
	this -> iVector[1] = 0;
}

void Snake::initTail()
{
	if (!this -> bFirstTailInit)
	{
		for (int i = 0; i < this -> iTailLen; ++i) delete this -> tail[i];
	}
	else
		this -> bFirstTailInit = false;
	this -> reset();
	int iStartPosX = wW / 2, iStartPosY = wH / 2;
	for (int i = 0; i < this -> iTailLenDefault; ++i)
	{
		this -> tail[i] = new RectangleShape(Vector2f(sqW, sqW));
		this -> tail[i] -> setPosition(iStartPosX, iStartPosY);
		this -> tail[i] -> setTexture(&(this -> tBoom));
		iStartPosX -= sqW;
	}
}

void Snake::addTailItem()
{
	RectangleShape* tailItem = new RectangleShape(Vector2f(sqW, sqW));
	tailItem -> setPosition(this -> tail[this -> iTailLen - 1] -> getPosition().x, this -> tail[this -> iTailLen - 1] -> getPosition().y);
	tailItem -> setTexture(&(this -> tBoom));
	RectangleShape** newTail = new RectangleShape* [this -> iTailLen + 1];
	for (int i = 0; i < this -> iTailLen; ++i)
		newTail[i] = this -> tail[i];
	newTail[this -> iTailLen] = tailItem;
	delete[] this -> tail;
	this -> tail = newTail;
	this -> iTailLen++;
}

int Snake::iTouchedTail()
{
	for (int i = this -> iTailLenDefault; i < this -> iTailLen; ++i)
	{
		int iTX = this -> tail[i] -> getPosition().x, iTY = this -> tail[i] -> getPosition().y;
		int iTailItemRect[4]{iTX, iTY, sqW, sqW};
		if (bCollideRect(this -> iGetHeadRect(), iTailItemRect)) return i;
	}
	return 0;
}

void Snake::spliceTail(int iTailItemIndex)
{
	RectangleShape** newTail = new RectangleShape* [iTailItemIndex];
	for (int i = 0; i < this -> iTailLen; ++i)
		if (i < iTailItemIndex) newTail[i] = this -> tail[i];
		else
			delete this -> tail[i];
	delete[] this -> tail;
	this -> tail = newTail;
	this -> iTailLen = iTailItemIndex;
}

bool Snake::bCollideWalls()
{
	int iX = this -> iHeadX() + sqW / 2, iY = this -> iHeadY() + sqW / 2;
	if (iX > wW - shrubW) return true;
	if (iX < shrubW) return true;
	if (iY > wH - shrubW) return true;
	if (iY < shrubW) return true;
	return false;
}

bool bOnlyKey(bool* bKeys, int len, int iKeyIndex)
{
	if (!bKeys[iKeyIndex]) return false;
	for (int i = 0; i < len; ++i)
		if (i != iKeyIndex && bKeys[i]) return false;
	return true;
}

void Snake::movement()
{
	int len = 4;
	bool bKeys[len]{
		Keyboard::isKeyPressed(Keyboard::W),
		Keyboard::isKeyPressed(Keyboard::S),
		Keyboard::isKeyPressed(Keyboard::A),
		Keyboard::isKeyPressed(Keyboard::D)
	};

	if (bOnlyKey(bKeys, len, 0) && this -> iVector[1] == 0)
	{
		this -> iVector[1] = -sqW;
		this -> iVector[0] = 0;
		this -> bTurn = true;
	}
	else if (bOnlyKey(bKeys, len, 1) && this -> iVector[1] == 0)
	{
		this -> iVector[1] = sqW;
		this -> iVector[0] = 0;
		this -> bTurn = true;
	}
	else if (bOnlyKey(bKeys, len, 2) && this -> iVector[0] == 0)
	{
		this -> iVector[0] = -sqW;
		this -> iVector[1] = 0;
		this -> bTurn = true;
	}
	else if (bOnlyKey(bKeys, len, 3) && this -> iVector[0] == 0)
	{
		this -> iVector[0] = sqW;
		this -> iVector[1] = 0;
		this -> bTurn = true;
	}
}