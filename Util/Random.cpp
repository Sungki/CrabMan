#include "Random.h"

#include <cstdlib>
#include <ctime>
#include <cmath>

namespace Random
{
	void init()
	{
		srand(time(nullptr));							// init for the random function
	}

	int range(int low, int high)
	{
		return rand() % (high - low + 1) + low;			// set the range of the random number
	}
}