#include <cmath>

bool bCollideRectY(int* iRect1, int* iRect2)
{
	int iHHalf = iRect1[3] / 2;
	int iDiffY = (iRect1[1] + iHHalf) - (iRect2[1] + iHHalf);
	if (abs(iDiffY) < iHHalf) return true;
	return false;
}

bool bCollideRectX(int* iRect1, int* iRect2)
{
	int iWHalf = iRect1[2] / 2;
	int iDiffX = (iRect1[0] + iWHalf) - (iRect2[0] + iWHalf);
	if (abs(iDiffX) < iWHalf) return true;
	return false;
}

bool bCollideRect(int* iRect1, int* iRect2)
{
	if (bCollideRectX(iRect1, iRect2) && bCollideRectY(iRect1, iRect2)) return true;
	return false;
}