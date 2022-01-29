class Game
{
	public:
		int FPS;
		bool bGameOver = false;
		int iDelay = 8;
		int iDelayCount = 0;
		int iScore = 0;
		int iMaxScore = 0;

		Game(int FPS);

		int iGetDelay()
		{
			return this -> iDelay;
		}
		int iGetDelayCount()
		{
			return this -> iDelayCount;
		}
		void setDelayCount(int value);
		void toggleGameOver();
		void setGameOver(bool value);
};