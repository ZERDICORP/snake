#include "../headers/map.h"

Map::Map(int FPS) : RenderWindow(VideoMode(wW, wH), "Snake")
{
	this -> setFramerateLimit(FPS);
	this -> load();
}

void Map::load()
{
	this -> tGround.loadFromFile("static/assets/ground.png");
	this -> sGround.setTexture(tGround);
	this -> sGround.setScale((float)wW / this -> tGround.getSize().x, (float)wH / this -> tGround.getSize().y);

	for (int i = 0; i < 3; ++i)
		this -> tShrub[i].loadFromFile("static/assets/shrub/shrub" + to_string(i) + ".png");
	
	for (int i = 0; i < 3; ++i)
		this -> sShrub[i].setTexture(this -> tShrub[i]);
	
	for (int i = 0; i < 3; ++i)
		this -> sShrub[i].setScale((float)shrubW / this -> tShrub[i].getSize().x, (float)shrubW / this -> tShrub[i].getSize().y);

	this -> Roboto_Light_Font.loadFromFile("static/fonts/Roboto-Light.ttf");

	this -> gameOverText.setFont(this -> Roboto_Light_Font);
	this -> gameOverText.setString("GAME OVER");
	this -> gameOverText.setCharacterSize(70);
	this -> gameOverText.setStyle(Text::Bold);
	this -> gameOverText.setFillColor(this -> textColor);

	this -> scoreText.setFont(this -> Roboto_Light_Font);
	this -> scoreText.setCharacterSize(30);
	this -> scoreText.setStyle(Text::Bold);
	this -> scoreText.setFillColor(this -> textColor);

	this -> clickEnterToReturnText.setFont(this -> Roboto_Light_Font);
	this -> clickEnterToReturnText.setString("click [Enter] to restart");
	this -> clickEnterToReturnText.setCharacterSize(22);
	this -> clickEnterToReturnText.setStyle(Text::Bold);
	this -> clickEnterToReturnText.setFillColor(this -> textColor);

	this -> score.setFont(this -> Roboto_Light_Font);
	this -> score.setCharacterSize(80);
	this -> score.setStyle(Text::Bold);
	this -> score.setFillColor(this -> textColor);

	this -> maxScore.setFont(this -> Roboto_Light_Font);
	this -> maxScore.setCharacterSize(25);
	this -> maxScore.setStyle(Text::Bold);
	this -> maxScore.setFillColor(this -> textColor);
}

void Map::drawBackground()
{
	this -> draw(this -> sGround);
}

void Map::drawWalls()
{
	int iShrubCols = wW / shrubW - 1, iShrubRows = wH / shrubW - 1;
	// ↓ [-top-]
	for (int i = 1; i < iShrubCols; ++i)
	{
		this -> sShrub[0].setPosition(i * shrubW, 0);
		this -> draw(this -> sShrub[0]);
	}
	// ↓ [-bottom-]
	for (int i = 1; i < iShrubCols; ++i)
	{
		this -> sShrub[0].setPosition(i * shrubW, wH - shrubW);
		this -> draw(this -> sShrub[0]);
	}
	// ↓ [-right-]
	for (int i = 1; i < iShrubRows; ++i)
	{
		this -> sShrub[1].setPosition(wW - shrubW, i * shrubW);
		this -> draw(this -> sShrub[1]);
	}
	// ↓ [-left-]
	for (int i = 1; i < iShrubRows; ++i)
	{
		this -> sShrub[1].setPosition(0, i * shrubW);
		this -> draw(this -> sShrub[1]);
	}
	// ↓ [-top left-]
	this -> sShrub[2].setPosition(0, 0);
	this -> draw(this -> sShrub[2]);
	// ↓ [-top right-]
	this -> sShrub[2].setRotation(90);
	this -> sShrub[2].setPosition(wW, 0);
	this -> draw(this -> sShrub[2]);
	// ↓ [-bottom right-]
	this -> sShrub[2].setRotation(180);
	this -> sShrub[2].setPosition(wW, wH);
	this -> draw(this -> sShrub[2]);
	// ↓ [-bottom left-]
	this -> sShrub[2].setRotation(270);
	this -> sShrub[2].setPosition(0, wH);
	this -> draw(this -> sShrub[2]);
	this -> sShrub[2].setRotation(0);
}

void Map::drawScore(int iScore, int iMaxScore)
{
	this -> score.setString(to_string(iScore));
	int iSW = this -> score.getLocalBounds().width, iSH = this -> score.getLocalBounds().height;
	this -> score.setPosition(wW / 2 - iSW / 2, wH / 2 - iSH / 2);

	int iMSW = this -> maxScore.getLocalBounds().width;
	this -> maxScore.setString(to_string(iMaxScore ? iMaxScore : iScore));
	this -> maxScore.setPosition(score.getPosition().x + iSW + iMSW, score.getPosition().y + iSH);

	this -> draw(score);
	this -> draw(maxScore);
}

void Map::showGameOver(int iScore)
{
	int w1 = this -> gameOverText.getLocalBounds().width, h1 = this -> gameOverText.getLocalBounds().height;
	int w2 = this -> scoreText.getLocalBounds().width, h2 = this -> scoreText.getLocalBounds().height;
	int w3 = this -> clickEnterToReturnText.getLocalBounds().width, h3 = this -> clickEnterToReturnText.getLocalBounds().height;
	
	int x1 = wW / 2 - w1 / 2, y1 = wH / 2 - (h1 + h2 / 2) - h1;
	int x2 = wW / 2 - w2 / 2, y2 = wH / 2 - (h2 / 2) - h3 / 2;
	int x3 = wW / 2 - w3 / 2, y3 = wH / 2 + (h2 / 2) + h3;

	this -> scoreText.setString("score: " + to_string(iScore));

	this -> gameOverText.setPosition(x1, y1);
	this -> scoreText.setPosition(x2, y2);
	this -> clickEnterToReturnText.setPosition(x3, y3);

	this -> draw(this -> gameOverText);
	this -> draw(this -> scoreText);
	this -> draw(this -> clickEnterToReturnText);
}