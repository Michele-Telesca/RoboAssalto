#pragma once
#include "point3D.h"
#include "weapon.h"

class weapon {

public:
	weapon();
	weapon(float lengthRange, float angleRange) : angleRange(angleRange), lengthRange(lengthRange){}

	float lengthRange; //lunghezza di mira
	float angleRange; //apertura della mira

	void drawTarget(); //disegna la mira... avrà bisogno della posizione del player e dalla direzione
	
	bool isShotArea(); //controlla se ci troviamo all'interno dell'area di mira

};

void weapon::drawTarget() {

}

bool weapon::isShotArea() {

}