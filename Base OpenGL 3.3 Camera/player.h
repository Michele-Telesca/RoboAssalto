#pragma once
#include "point3D.h"
#include "weapon.h"
#include "model.h"

class player {

public:
	
	player() {}

	player(float x, float y, float z) : x(x), y(y), z(z) {}

	float x;//centro utente
	float y;
	float z;

	//point3D direction; //punto in cui si trova il cursore verrà aggiornato e non fa parte del costruttore

	unsigned int texturePlayer;

	int life; //vita del player aggiornata 
	int numShotsAvailable; //colpi a disposizione
	float chargingTime; //tempo di ricarica del colpo
	float timeLastShot; //tempo dell'ultimo colpo. servirà in update per calcolare se è passato abbastanza tempo per ricaricare  

	Model* player_model;

	weapon* weapon; //arma posseduta al momento

	void drawPlayer(Shader myShader); //disegna il player
	void animate(); //metodo di servizio per l'animazione
	void initPlayer();

	void moveDx();
	void moveSx();
	void moveUp();
	void moveDown();

	float getX() {
		return x;
	}

	float getY() {
		return y;
	}

	float getZ() {
		return z;
	}

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

	//caricamento modello
	player_model = new Model();
	player_model->loadModel("models/Michelle/Ch03_nonPBR.DAE");

}

void player::drawPlayer(Shader myShader) {

	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, texturePlayer);
	//glBindVertexArray(cubeVAO);

	//myShader.setVec3("colorcube", 1.0f, 1.0f, 1.0f); //bianco (colore neutro)

	//// creo la singola mattonella del floor e la inserisco nel vettore tiles
	//cube* playerMesh = new cube(1.0f, 0.0f, 1.0f, 0.0f, 0.0f, x, y, z);
	//playerMesh->drawCube(myShader);

	//glBindTexture(GL_TEXTURE_2D, 0);

	myShader.setVec3("colorcube", 1.0f, 1.0f, 1.0f); //bianco (colore neutro)

	glm::mat4 model = glm::mat4(1.0f);	
	model = glm::translate(model, glm::vec3(x, 2.0f, z));
	model = glm::rotate(model, 0.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));
	myShader.setMat4("model", model);

	player_model->Draw(myShader);

}

void player::animate() {

}

void player::moveDx() {
	x = x + 0.3f;
}

void player::moveSx() {
	x = x  - 0.3f;
}

void player::moveUp() {
	z = z - 0.3f;
}

void player::moveDown() {
	z = z + 0.3f;
}