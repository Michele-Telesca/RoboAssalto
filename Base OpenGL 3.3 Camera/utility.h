#pragma once
#include <vector>

class utility
{
};

float randMToN(int M, int N) {
	return M + (rand() / (RAND_MAX / (N - M)));
}

bool numeroGiaPresente(int numero, vector<int> lista) {
	for (int i = 0; i < lista.size(); i++) {
		if (numero == lista[i]) {
			return true; //numero presente
		}
	}
	return false; //numero non presete
}

//restituisce true se a = b a meno di un valore epsilon (molto piccolo). Risolve il problema del confronto tra float
bool isEqual(float a, float b, float epsilon)
{
	return fabs(a - b) < epsilon;
}


