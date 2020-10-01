#pragma once
#include "model.h"
#include "weapon.h"
#include "skinned_mesh.h"
#include "globalData.h"
#include "playerShot.h"
//#include "villain.h"


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
	float anglePlayer;

	// modello 3D con scheletro e animazione
	SkinnedMesh meshRunning;
	SkinnedMesh meshStanding;

	//float animationCounter = 0.0f;

	weapon* wea = new weapon(3.0f, 90.0f, 2.0f); //arma posseduta al momento
	
	bool mouseSxIsSelected = false;
	bool startPlayerShot = false;

	//lista colpi
	playerShot listShot[numShot];

	unsigned int texturePlayer;

	//prototipi
	void drawPlayer(Shader animShader, Shader lightShader, glm::mat4 view, glm::vec3 mousePoint); //disegna il player
	void initPlayer(); //inizializza il player
	void updateAngleShot(float tempDegree, float anglePlayer);
	//get e set

	bool getStartPlayerShot() {
		return startPlayerShot;
	}

	float getX() {
		return x;
	}

	float getY() {
		return y;
	}

	float getZ() {
		return z;
	}

	float getAnglePlayer() {
		return anglePlayer;
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

	void setAnglePlayer(float angle) {
		anglePlayer = angle;
	}

	

};

void player::initPlayer() {

	//punto in cui nasce
	x = 0.0f;
	y = 0.5f;
	z = 0.0f;

	anglePlayer = 0.0f;
	//vita iniziale
	life = 100;

	//numero colpi a disposizione
	numShotsAvailable = 3;

	//tempo ricarica colpo
	chargingTime = 0.0;

	//tempo ultimo colpo
	timeLastShot = 0.0;


	//inizializzo la lista dei colpi
	for (int i = 0; i < numShot; i++) {
		listShot[i].inizializza();
	}

	//loading meshes with animation
	//meshRunning.loadMesh("animation/player_michelle/running/Running.dae");
	meshRunning.loadMesh("animation/player_michelle/shotgun_running/shotgun_running.dae");
	meshStanding.loadMesh("animation/player_michelle/shotgun_standing/shotgun_standing.dae");

}

float angleBetween(const glm::vec3 a, const glm::vec3 b) {

	float angle = atan2(b.x, a.x) - atan2(b.z, a.y);
	return angle;
}

bool checkShotIsAvaiable(int numShot, float chargingTime, float timeLastShot) {
	if (numShot == 0) {
		return false;
	}
	return true;
}

void player::updateAngleShot(float tempDegree, float anglePlayer) {

	if (tempDegree > 0 and tempDegree < 90) {
		setAnglePlayer(45.0f);
	}
	if (tempDegree > 90 and tempDegree < 180) {
		setAnglePlayer(135.0f);
	}
	if (tempDegree < 0 and tempDegree > -90) {
		setAnglePlayer(315.0f);
	}
	if (tempDegree < -90 and tempDegree > -180) {
		setAnglePlayer(225.0f);
	}
}

void player::drawPlayer(Shader animShader, Shader lightShader, glm::mat4 view, glm::vec3 mousePoint) {
	
	float mouseX = mousePoint.x;
	float mouseY = mousePoint.z;

	float d1 = mouseX - x;
	float d2 = mouseY - z;

	float angleWeapon = atan2(d1, d2);

	animShader.use();
	
	//projection
	glm::mat4 projection = glm::mat4(1.0f);	//identity matrix
	projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	animShader.setMat4("projection", projection);

	//view
	animShader.setMat4("view", view);
	
	float radiansAngle = glm::radians(anglePlayer);

	if (startPlayerShot) {
		radiansAngle = angleWeapon;
		float tempDegree = glm::degrees(radiansAngle);

		updateAngleShot(tempDegree, anglePlayer);
		
		//cout << "*** angle player (X,Z): (" << anglePlayer << ")" << endl;
		//cout << "*** angle Mouse: (" << tempDegree << ")" << endl;

	}

	//model
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(x, 0.5f, z));
	model = glm::rotate(model, radiansAngle, glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f)); //per metterlo in posizione verticale sul pavimento
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
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
	
	

	//controllo la lista dei colpi e ne setto gli angoli 
	if (startPlayerShot) {
		bool shotIsAvaiable = checkShotIsAvaiable(numShotsAvailable, chargingTime, timeLastShot);
		if (shotIsAvaiable) {
			listShot[numShotsAvailable - 1].x = x;
			listShot[numShotsAvailable - 1].y = y;
			listShot[numShotsAvailable - 1].z = z;
			listShot[numShotsAvailable - 1].startX = x;
			listShot[numShotsAvailable - 1].startZ = z;
			listShot[numShotsAvailable - 1].angle = angleWeapon;
			listShot[numShotsAvailable - 1].isShot = true;
			numShotsAvailable = numShotsAvailable - 1;
		}
		startPlayerShot = false;
	}

	if (mouseSxIsSelected) {
		wea->drawTarget(lightShader, view, x, y, z, texturePlayer, angleWeapon);
	}

	// material properties
	lightShader.setVec3("material.ambient", 1.0f, 1.0f, 1.0f);
	lightShader.setVec3("material.diffuse", 1.0f, 1.0f, 1.0f);
	lightShader.setVec3("material.specular", 1.0f, 1.0f, 1.0f);
	lightShader.setFloat("material.shininess", 76.8f);


	for (int i = 0; i < numShot; i++) {
		if (listShot[i].isShot) {
			listShot[i].draw(lightShader, texturePlayer);
		}
	}



}

