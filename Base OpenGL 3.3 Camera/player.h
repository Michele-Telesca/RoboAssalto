#pragma once
#include "model.h"
#include "weapon.h"
#include "skinned_mesh.h"
#include "globalData.h"
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
	float anglePlayer;
	// modello 3D del player
	SkinnedMesh meshRunning;
	SkinnedMesh meshStanding;
	SkinnedMesh meshAttacking;

	//float animationCounter = 0.0f;

	weapon* wea = new weapon(3.0f, 90.0f, 2.0f); //arma posseduta al momento
	
	bool mouseSxIsSelected = false;

	unsigned int texturePlayer;

	//prototipi
	void drawPlayer(Shader animShader, Shader lightShader, glm::mat4 view, glm::vec3 mousePoint); //disegna il player
	void initPlayer(); //inizializza il player
	void calculateAngle();

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

	anglePlayer = true;
	//vita iniziale
	life = 100;

	//numero colpi a disposizione
	numShotsAvailable = 3;

	//tempo ricarica colpo
	chargingTime = 0.0;

	//tempo ultimo colpo
	timeLastShot = 0.0;

	//loading meshes with animation
	meshRunning.loadMesh("animation/player_michelle/running/Running.dae");
	meshStanding.loadMesh("animation/player_michelle/standing/Idle.dae");
	meshAttacking.loadMesh("animation/player_michelle/kick/Flying Kick.dae");

}

float angleBetween(const glm::vec3 a, const glm::vec3 b) {

	float angle = atan2(b.x, a.x) - atan2(b.z, a.y);
	return angle;
}

void player::drawPlayer(Shader animShader, Shader lightShader, glm::mat4 view, glm::vec3 mousePoint) {
	
	animShader.use();

	calculateAngle();
	
	//projection
	glm::mat4 projection = glm::mat4(1.0f);	//identity matrix
	projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	animShader.setMat4("projection", projection);

	//view
	animShader.setMat4("view", view);
	
	//model
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(x, 0.5f, z));
	model = glm::rotate(model, glm::radians(anglePlayer), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));
	animShader.setMat4("model", model);

	vector <glm::mat4> transforms;

	if (muoviDx == false && muoviSx == false && muoviSu == false && muoviGiu == false) { //se non mi muovo -> meshStanding
		meshStanding.boneTransform(animationTime_player, transforms);
		glUniformMatrix4fv(glGetUniformLocation(animShader.ID, "bones"),
			transforms.size(),
			GL_FALSE,
			glm::value_ptr(transforms[0]));
		meshStanding.render();
	}
	else if (muoviDx == true || muoviSx == true || muoviSu == true || muoviGiu == true) { //se mi muovo -> meshRunning
		
		meshRunning.boneTransform(animationTime_player, transforms);
		glUniformMatrix4fv(glGetUniformLocation(animShader.ID, "bones"),
			transforms.size(),
			GL_FALSE,
			glm::value_ptr(transforms[0]));
		meshRunning.render();

	}



	float mouseX = mousePoint.x;
	float mouseY = mousePoint.z;

	float d1 = mouseX - x;
	float d2 = mouseY - z;

	float angle = atan2(d1, d2);

	if (mouseY < z) {
		//angle = - 3.14f;
	}

	if (mouseSxIsSelected) {
		wea->drawTarget(lightShader, view, x, y, z, texturePlayer, angle);
	}
}

void player::calculateAngle() {

	if (muoviDx == true) {
		anglePlayer = 90.0f;
		if (muoviSu == true) {
			anglePlayer = 135.0f;
		}
		if (muoviGiu == true) {
			anglePlayer = 45.0f;
		}
	}
	if (muoviSx == true) {
		anglePlayer = 270.0f;
		if (muoviSu == true) {
			anglePlayer = 225.0f;
		}
		if (muoviGiu == true) {
			anglePlayer = 315.0f;
		}
	}

	if (muoviGiu == true) {
		if (muoviDx == false && muoviSx == false) {
			anglePlayer = 0.0f;
		}
	}
	if (muoviSu == true) {
		if (muoviDx == false && muoviSx == false) {
			anglePlayer =  180.0;
		}
	}
}


