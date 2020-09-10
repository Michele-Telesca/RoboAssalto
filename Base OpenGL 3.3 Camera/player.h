#pragma once
#include "point3D.h"
#include "weapon.h"
#include "model.h"

class player {

public:
	
	player() {}

	player(float x, float y, float z) : x(x), y(y), z(z) {}
	
	//coordinate
	float x; 
	float y;
	float z;

	int life; //vita del player aggiornata 
	int numShotsAvailable; //colpi a disposizione
	float chargingTime; //tempo di ricarica del colpo
	float timeLastShot; //tempo dell'ultimo colpo. servirà in update per calcolare se è passato abbastanza tempo per ricaricare  

	// modello 3D del player
	Model* player_model;

	weapon* weapon; //arma posseduta al momento

	void drawPlayer(Shader myShader); //disegna il player
	void animate(); //animazione del player
	void initPlayer(); //inizializza il player

	//movimenti
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
	//player_model->loadModel("models/Stones/Stone1.obj");

	player_model->loadModel("models/Michelle/Ch03_nonPBR.DAE");

}

void player::drawPlayer(Shader lightShader) {

	// material properties
	lightShader.setVec3("material.ambient", 1.0f, 1.0f, 1.0f);
	lightShader.setVec3("material.diffuse", 1.0f, 1.0f, 1.0f);
	lightShader.setVec3("material.specular", 1.0f, 1.0f, 1.0f);
	lightShader.setFloat("material.shininess", 76.8f);

	glm::mat4 model = glm::mat4(1.0f);	
	model = glm::translate(model, glm::vec3(x, 2.0f, z));
	model = glm::rotate(model, 0.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));
	lightShader.setMat4("model", model);

	player_model->Draw(lightShader);

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