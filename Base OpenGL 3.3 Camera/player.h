#pragma once
#include "point3D.h"
#include "weapon.h"

class player {

public:
	
	player(point3D pcenter): center(pcenter) {}

	
	point3D center; //centro utente
	point3D direction; //punto in cui si trova il cursore verrà aggiornato e non fa parte del costruttore

	int life; //vita del player aggiornata 
	int numShotsAvailable; //colpi a disposizione
	float chargingTime; //tempo di ricarica del colpo
	float timeLastShot; //tempo dell'ultimo colpo. servirà in update per calcolare se è passato abbastanza tempo per ricaricare  
	
	weapon weapon; //arma posseduta al momento

	void draw(); //disegna il player
	void animate(); //metodo di servizio per l'animazione

};

void player::draw() {

}

void player::animate() {

}