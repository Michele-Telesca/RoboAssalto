#pragma once
#include "point3D.h"
#include "weapon.h"

class villain {

public:

	villain(point3D pcenter) : center(pcenter) {}

	point3D center; //centro utente

	int life; //vita del player aggiornata 

	float chargingTime; //tempo di ricarica del colpo
	float timeLastShot; //tempo dell'ultimo colpo. serve per dare un tempo tra l'ultimo colpo e il prossimo

	weapon weapon; //per avere la gittata del villain

	void draw(); //disegna il player
	void animate(); //metodo di servizio per l'animazione

};

void villain::draw() {

}

void villain::animate() {

}
