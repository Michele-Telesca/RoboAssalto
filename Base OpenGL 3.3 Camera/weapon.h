#pragma once
#include "point3D.h"
#include "weapon.h"

class weapon {

public:

	weapon() {};
	//costruttore per tutte le armi
	weapon(float lengthRange, float angleRange,float lengthBase) : angleRange(angleRange), lengthRange(lengthRange), lengthBase(lengthBase){}

	float lengthRange; //lunghezza di mira
	float lengthBase;
	float angleRange; //apertura della mira

	void drawTarget(); //disegna la mira... avrà bisogno della posizione del player e dalla direzione
	
	bool isShotArea(); //controlla se ci troviamo all'interno dell'area di mira
	void initWeapon();

};

//init arma iniziale
void weapon::initWeapon() {
	
	lengthRange = 4.0f;
	lengthBase = 2.0f;
	angleRange = 90.0f;

}

void weapon::drawTarget() {

}

bool weapon::isShotArea() {
	return false;
}