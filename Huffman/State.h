#pragma once
struct State
{
	size_t shiftPos;
	size_t i;
	size_t bitsUsed;
	size_t bitsSize;
	const unsigned char* content;
	bool inRange()
	{
		return bitsSize > bitsUsed; 
	}
	int nextBit()
	{

		if (shiftPos == -1)
		{
			i++;
			shiftPos = 7;
		}
		//82*shiftpos
		int temp = content[i] & (1 << (shiftPos));
		temp >>= shiftPos;
		shiftPos--;
		bitsUsed++;
		return temp;
	}
	int bitsShifted()
	{
		return 8 - shiftPos;
	}
	State(size_t i = 0, size_t shiftPos = 7) : i(i), shiftPos(shiftPos) {};

};