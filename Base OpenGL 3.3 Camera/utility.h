#pragma once
#include <stdlib.h>

class utility
{
};

float randMToN(float M, float N) {
	return M + (rand() / (RAND_MAX / (N - M)));
}

