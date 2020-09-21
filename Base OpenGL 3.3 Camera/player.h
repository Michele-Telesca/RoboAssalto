#pragma once
#include "point3D.h"
#include "weapon.h"
#include "model.h"
#include "gameMap.h"
#include "globalData.h"

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

	void drawPlayer(Shader myShader, glm::vec3 mousePoint); //disegna il player
	void animate(); //animazione del player
	void initPlayer(); //inizializza il player

	//movimenti
	void moveDx();
	void moveSx();
	void moveUp();
	void moveDown();
	bool mouseSxIsSelected = false;

	unsigned int texturePlayer;

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

void player::moveDx() {
    float epsilon = 0.001;

	bool ostacolo = false;
	for (int i = 0; i < mapObjectsCoord.size(); i++) {
		float x_obj = (float)mapObjectsCoord[i].x;
		float z_obj = (float)mapObjectsCoord[i].y;
		if (isEqual(x, x_obj - (TILE_DIM / 2 + MOVE_STEP), EPSILON_1) && (z >= z_obj - TILE_DIM / 2 && z <= z_obj + TILE_DIM / 2)) {
			ostacolo = true;
			exit;
		}
	}
	if (ostacolo == true) {
		x = x;
	}
	else {
		x = x + MOVE_STEP;
	}
}

void player::moveSx() {
	float epsilon = 0.001;
	bool ostacolo = false;
	for (int i = 0; i < mapObjectsCoord.size(); i++) {
		float x_obj = (float)mapObjectsCoord[i].x;
		float z_obj = (float)mapObjectsCoord[i].y;
		if (isEqual(x, x_obj + (TILE_DIM / 2 + MOVE_STEP), EPSILON_1) && (z >= z_obj - TILE_DIM / 2 && z <= z_obj + TILE_DIM / 2)) {
			ostacolo = true;
			exit;
		}
	}
	if (ostacolo == true) {
		x = x;
	}
	else {
		x = x - MOVE_STEP;
	}
}

void player::moveUp() {
	float epsilon = 0.001;
	bool ostacolo = false;
	for (int i = 0; i < mapObjectsCoord.size(); i++) {
		float x_obj = mapObjectsCoord[i].x;
		float z_obj = mapObjectsCoord[i].y;
		if ((x >= x_obj - TILE_DIM / 2 && x <= x_obj + TILE_DIM / 2) && isEqual(z, z_obj + (TILE_DIM / 2 + MOVE_STEP), EPSILON_1)) {
			ostacolo = true;
			exit;
		}
	}
	if (ostacolo == true) {
		z = z;
	}
	else {
		z = z - MOVE_STEP;
	}
}

void player::moveDown() {
	float epsilon = 0.001;
	bool ostacolo = false;
	for (int i = 0; i < mapObjectsCoord.size(); i++) {
		float x_obj = mapObjectsCoord[i].x;
		float z_obj = mapObjectsCoord[i].y;
		if ((x >= x_obj - TILE_DIM / 2 && x <= x_obj + TILE_DIM / 2) && isEqual(z, z_obj - (TILE_DIM / 2 + MOVE_STEP), EPSILON_1)) {
			ostacolo = true;
			exit;
		}
	}
	if (ostacolo == true) {
		z = z;
	}
	else {
		z = z + MOVE_STEP;
	}
}