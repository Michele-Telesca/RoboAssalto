#pragma once
#include "model.h"
#include "weapon.h"
//#include "villain.h"


class player {

public:

	player() {}

	player(float x, float y, float z) : x(x), y(y), z(z) {}

	float angleP = 0.0f;

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

	weapon* wea = new weapon(3.0f, 90.0f, 2.0f); //arma posseduta al momento
	
	bool mouseSxIsSelected = false;

	unsigned int texturePlayer;

	//prototipi
	void drawPlayer(Shader myShader, glm::vec3 mousePoint); //disegna il player
	void animate(); //animazione del player
	void initPlayer(); //inizializza il player

	//get e set
	float getX() {
		return x;
	}

	float getY() {
		return y;
	}

	float getZ() {
		return z;
	}

	void setX(float new_x) {
		x = new_x;
	}

	void setY(float new_y) {
		y = new_y;
	}

	void setZ(float new_z) {
		z = new_z;
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

	//caricamento modello
	player_model = new Model();
	player_model->loadModel("models/michelle/Ch03_nonPBR.DAE");
}

float angleBetween(const glm::vec3 a, const glm::vec3 b) {

	float angle = atan2(b.x, a.x) - atan2(b.z, a.y);
	return angle;
}

void player::drawPlayer(Shader lightShader, glm::vec3 mousePoint) {

	// material properties
	lightShader.setVec3("material.ambient", 1.0f, 1.0f, 1.0f);
	lightShader.setVec3("material.diffuse", 1.0f, 1.0f, 1.0f);
	lightShader.setVec3("material.specular", 1.0f, 1.0f, 1.0f);
	lightShader.setFloat("material.shininess", 76.8f);

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(x, 0.5f, z));
	model = glm::rotate(model, 0.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));
	lightShader.setMat4("model", model);


	float mouseX = mousePoint.x;
	float mouseY = mousePoint.z;

	float d1 = mouseX - x;
	float d2 = mouseY - z;

	float angle = atan2(d1, d2);

	if (mouseY < z) {
		//angle = - 3.14f;
	}
	

	player_model->Draw(lightShader);

	if (mouseSxIsSelected) {
		wea->drawTarget(lightShader, x, y, z, texturePlayer, angle);
	}
}

void player::animate() {

}
