#pragma once

class utility
{
};

float randMToN(float M, float N) {
	return M + (rand() / (RAND_MAX / (N - M)));
}

//restituisce true se a = b a meno di un valore epsilon (molto piccolo). Risolve il problema del confronto tra float
bool isEqual(float a, float b, float epsilon)
{
	return fabs(a - b) < epsilon;
}


