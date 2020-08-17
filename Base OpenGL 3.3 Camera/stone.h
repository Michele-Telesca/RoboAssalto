#pragma once
#include "point3D.h"
#include "weapon.h"

class stone { //potrebbe essere utilizzato anche per l'albero 

public:

	stone(point3D pcenter) : center(pcenter) {}

	point3D center; //centro utente
	
	bool destroyed; //true se la roccia è distrutta

	void draw(); //disegna il player

};

void stone::draw() {

}

