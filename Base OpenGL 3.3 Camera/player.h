#pragma once
#include "point3D.h"
#include "weapon.h"

class player {

public:
	
	player() {}

	player(float x, float y, float z) : x(x), y(y), z(z) {}

	float x;//centro utente
	float y;
	float z;

	point3D direction; //punto in cui si trova il cursore verrà aggiornato e non fa parte del costruttore

	unsigned int texturePlayer;

	int life; //vita del player aggiornata 
	int numShotsAvailable; //colpi a disposizione
	float chargingTime; //tempo di ricarica del colpo
	float timeLastShot; //tempo dell'ultimo colpo. servirà in update per calcolare se è passato abbastanza tempo per ricaricare  
	
	weapon* weapon; //arma posseduta al momento

	void draw(); //disegna il player
	void animate(); //metodo di servizio per l'animazione
	void initPlayer();

};

void player::initPlayer() {

	//punto in cui nasce
	x = 0.0f;
	y = 0.5f;
	z = 0.0f;

	//vita iniziale
	life = 100;

	//numero colpi a disposizione
	numShotsAvailable = 3;

	//tempo ricarica colpo
	chargingTime = 0.0;

	//tempo ultimo colpo
	timeLastShot = 0.0;

	//arma iniziale
	weapon->initWeapon();

}

void player::draw() {

	// setto la texture
	glActiveTexture(GL_TEXTURE0);

	glBindTexture(GL_TEXTURE_2D, texturePlayer);
	glBindVertexArray(cubeVAO);

	myShader->setVec3("colorcube", 1.0f, 1.0f, 1.0f); //bianco (colore neutro)

	// creo la singola mattonella del floor e la inserisco nel vettore tiles
	cube* playerMesh = new cube(1.0f, 0.0f, 1.0f, 0.0f, 0.0f, x, y, z, myShader);
	playerMesh->drawCube();

	glBindTexture(GL_TEXTURE_2D, 0);

}

void player::animate() {

}