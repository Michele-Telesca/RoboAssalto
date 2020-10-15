#pragma once
#include "model.h"
#include "weapon.h"
#include "skinned_mesh.h"
#include "globalData.h"
#include "playerShot.h"
//#include "villain.h"
#include <irrKlang/irrKlang.h>


class player {

public:

	player() {}

	//coordinate
	float x;
	float y;
	float z;

	float life; //vita del player aggiornata 
	int chest_life;
	float lifeMax;

	int numShotsAvailable; //colpi a disposizione
	float chargingTime;    //tempo di ricarica del colpo
	float timeLastShot;    //tempo dell'ultimo colpo. servirà in update per calcolare se è passato abbastanza tempo per ricaricare  
	float delayShotTime;
	bool delayShotIsFinished;
	float anglePlayer;

	bool mouseSxIsSelected = false;
	bool startPlayerShot = false;

	// modelli 3D con scheletro e animazione
	SkinnedMesh meshRunning;
	SkinnedMesh meshStanding;

	// tempo per le animazioni
	float animationTime_playerStanding;
	float animationTime_playerRunning;
	
	// target dell'arma
	weapon* wea;  //arma posseduta al momento

	//lista colpi
	vector<playerShot*> listShot;

	//texture
	unsigned int texture1;
	unsigned int textureLife;
	unsigned int textureShotBar;

	//prototipi
	void drawPlayer(Shader animShader, Shader lightShader, glm::vec3 mousePoint); //disegna il player
	void animatePlayer(Shader animShader);
	void initPlayer(int selectedPlayer); //inizializza il player
	void updateAngleShot(float tempDegree, float anglePlayer);
	bool checkShotIsAvaiable(float currentTime);
	void drawLifePlayer(Shader lightShader);
	void drawShotAvaiable(int numShotsAvailable, float currentTime, Shader lightShader);
	bool checkShotDelay(float currentTime);

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

	void setTimeLastShot(float time) {
		timeLastShot = time;
	}
	void setNumShotAvailable(int numShot) {
		numShotsAvailable = numShot;
	}

	void addNumShotAvailable() {
		numShotsAvailable = numShotsAvailable + 1;
	}

	void removeShot() {
		numShotsAvailable = numShotsAvailable -1;
	}

	int getNumShot() {
		numShotsAvailable;
	}

};

void player::initPlayer(int selectedPlayer) {

	wea =  new weapon(WEAPON_SHOTGUN);

	//SoundEngine = irrklang::createIrrKlangDevice();

	//punto in cui nasce
	x = 0.0f;
	y = 0.5f;
	z = 0.0f;

	anglePlayer = 0.0f;

	//vita iniziale

	life = 100.0;
	chest_life = 200;

	lifeMax = life;

	//numero colpi a disposizione
	setNumShotAvailable(numShot);

	//tempo ricarica colpo
	chargingTime = 5.0f;

	//tempo ultimo colpo
	timeLastShot = 0.0f;

	//inizializzo la lista dei colpi
	for (int i = 0; i < numShot; i++) {
		playerShot* playerShot_i = new playerShot();
		listShot.push_back(playerShot_i);
		listShot[i]->inizializza();
	}

	//loading meshes with animation
	if (selectedPlayer == PLAYER_MICHELLE) {
		//michelle
		meshRunning.loadMesh("animation/player_michelle/shotgun_running/shotgun_running.dae");
		meshStanding.loadMesh("animation/player_michelle/shotgun_standing/shotgun_standing.dae");
	}
	else if (selectedPlayer == PLAYER_BRYCE) {
		//bryce
		meshRunning.loadMesh("animation/player_bryce/shotgun_running/shotgun_running.dae");
		meshStanding.loadMesh("animation/player_bryce/shotgun_standing/shotgun_standing.dae");
	}

	// tempo per le animazioni
	animationTime_playerStanding = 0.0f;
	animationTime_playerRunning = 0.0f;
	
	delayShotTime = 0.0f; //delay tra uno sparo e un altro
	delayShotIsFinished = true;

}

float angleBetween(const glm::vec3 a, const glm::vec3 b) {

	float angle = atan2(b.x, a.x) - atan2(b.z, a.y);
	return angle;
}

bool player::checkShotDelay(float currentTime) { //tempo tra uno shot e un altro di file
	if (wea->weapon_type == WEAPON_SHOTGUN) {
		if (delayShotTime == 0.0f || (currentTime - delayShotTime) > DELAY_SHOTGUN) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		if (delayShotTime == 0.0f || (currentTime - delayShotTime) > DELAY_SNIPER) {
			return true;
		}
		else {
			return false;
		}
	}

}

bool player::checkShotIsAvaiable(float currentTime) {
	//controllo se gli shot disponibili sono minori di tre e se è passato il tempo necessario per caricare un colpo
	if (numShotsAvailable == 3) {
		setTimeLastShot(currentTime);
	}
	if (numShotsAvailable < 3) {
		if ((currentTime - timeLastShot) > chargingTime) {
			addNumShotAvailable();
			setTimeLastShot(currentTime);
			return true;
		}
	}
	//se i colpi disponibili sono minori di 0 non posso sparare oppure il tempo passato dal lastshot è inferiore a tot
	if (numShotsAvailable == 0) {
		return false;
	}
	//se ho colpi disponibili setto il tempo di lastShot e torno true
	//setTimeLastShot(currentTime);

	return true;
}

void player::updateAngleShot(float tempDegree, float anglePlayer) {

	for (float ang = 0.0f; ang < 180.0f; ang = ang + 15.0f) {
		float tempAng = ang + 15.0f;
		if (tempDegree >= ang && tempDegree < tempAng) {
			setAnglePlayer(ang);
		}
	}
	for (float ang = -180.0f; ang < 0.0f; ang = ang + 15.0f) {
		float tempAng = ang + 15.0f;
		if (tempDegree >= ang && tempDegree < tempAng) {
			setAnglePlayer(ang + 360.0f);
		}
	}
}

void player::drawPlayer(Shader simpleShader, Shader animShader, glm::vec3 mousePoint) {
	
	// ----- PLAYER ----- //

	float mouseX = mousePoint.x;
	float mouseY = mousePoint.z;

	float d1 = mouseX - x;
	float d2 = mouseY - z;

	float angleWeapon = atan2(d1, d2);

	//setto lo shader per il player
	animShader.use();
	
	float radiansAngle = glm::radians(anglePlayer);

	if (startPlayerShot) {
		radiansAngle = angleWeapon;
		float tempDegree = glm::degrees(radiansAngle);

		updateAngleShot(tempDegree, anglePlayer);

	}

	//model
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(x, 0.5f, z));
	model = glm::rotate(model, radiansAngle, glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f)); //per metterlo in posizione verticale sul pavimento
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
	animShader.setMat4("model", model);	

	//material properties
	animShader.setVec3("material.ambient", 0.9f, 0.9f, 0.9f);
	animShader.setVec3("material.diffuse", 0.8f, 0.8f, 0.8f);
	animShader.setVec3("material.specular", 0.1f, 0.1f, 0.1f);
	animShader.setFloat("material.shininess", 76.8f);

	animatePlayer(animShader); //animazione player


	// ----- TARGET - SHOT - LIFE ----- //

	//controllo la lista dei colpi e ne setto gli angoli 
	float currentTime = glfwGetTime();
	bool shotIsAvaiable = checkShotIsAvaiable(currentTime);
	delayShotIsFinished = checkShotDelay(currentTime);

	if (startPlayerShot) {
		if (shotIsAvaiable && delayShotIsFinished) {
			delayShotTime = currentTime;
			listShot[numShotsAvailable - 1]->startX = x; //posizione x del player
			listShot[numShotsAvailable - 1]->startZ = z; //posizione z del player
			listShot[numShotsAvailable - 1]->angle = angleWeapon;
			listShot[numShotsAvailable - 1]->isShot = true;

			removeShot();

		}
		startPlayerShot = false;
	}

	//DRAW TARGET
	if (mouseSxIsSelected) {
		wea->drawTarget(simpleShader, x, y, z, texture1, angleWeapon);
	}

	//DRAW SHOT
	for (int i = 0; i < numShot; i++) {
		if (listShot[i]->isShot) {
			if (wea->lengthBase == LENGTH_BASE_SHOTGUN) {
				listShot[i]->drawPlayerShot(simpleShader, texture1, SHOT_DIM2);
			}
			else {
				listShot[i]->drawPlayerShot(simpleShader, texture1, SHOT_DIM);
			}
		}
	}

	//DRAW LIFE_INTERFACE
	if (life > 0.0f) {
		drawLifePlayer(simpleShader);
	}

	//DRAW SHOT_INTERFACE
	drawShotAvaiable(numShotsAvailable, currentTime, simpleShader);
}

void player::animatePlayer(Shader animShader) {
	vector <glm::mat4> transforms;

	if (muoviDx == false && muoviSx == false && muoviSu == false && muoviGiu == false) { //se non mi muovo -> meshStanding
		meshStanding.boneTransform(animationTime_playerStanding, transforms);
		glUniformMatrix4fv(glGetUniformLocation(animShader.ID, "bones"),
			transforms.size(),
			GL_FALSE,
			glm::value_ptr(transforms[0]));
		meshStanding.render();
	}
	else if (muoviDx == true || muoviSx == true || muoviSu == true || muoviGiu == true) { //se mi muovo -> meshRunning		
		meshRunning.boneTransform(animationTime_playerRunning, transforms);
		glUniformMatrix4fv(glGetUniformLocation(animShader.ID, "bones"),
			transforms.size(),
			GL_FALSE,
			glm::value_ptr(transforms[0]));
		meshRunning.render();
	}
}

void player::drawShotAvaiable(int numShotsAvailable, float currentTime, Shader simpleShader) {
	
	simpleShader.use();

	float shotBarLenght = (lifeMax / 3.0f) / lifeMax;
	float shotHalfBar = (shotBarLenght / 2.0);
	float center = x - shotBarLenght;

	for (int i = 0; i < numShotsAvailable; i++) {

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureShotBar);
		glBindVertexArray(cubeVAO);

		//lightShader.setVec3("colorcube", 1.0f, 0.0f, 0.0f);
		glm::mat4 modelLife = glm::mat4(1.0f);

		modelLife = glm::translate(modelLife, glm::vec3(center + (shotBarLenght*i), y + 2.22f, z));
		modelLife = glm::rotate(modelLife, 3.14f / 2.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		modelLife = glm::translate(modelLife, glm::vec3(0.0f, 0.0f, 0.0f));
		modelLife = glm::scale(modelLife, glm::vec3(shotBarLenght - 0.03f, 0.01f, 0.15f));

		simpleShader.setMat4("model", modelLife);

		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	if (numShotsAvailable < 3) {

		float lenghtCalcShot = ((currentTime - timeLastShot) * shotBarLenght)/chargingTime;

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glBindVertexArray(cubeVAO);

		//lightShader.setVec3("colorcube", 1.0f, 0.0f, 0.0f);
		glm::mat4 modelLife = glm::mat4(1.0f);


		float centerCalcStart = (center + (shotBarLenght * (numShotsAvailable))) - shotHalfBar;
		float centerCalc = centerCalcStart + (lenghtCalcShot/2.0f);

		modelLife = glm::translate(modelLife, glm::vec3(centerCalc, y + 2.22f, z));
		modelLife = glm::rotate(modelLife, 3.14f / 2.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		modelLife = glm::translate(modelLife, glm::vec3(0.0f, 0.0f, 0.0f));
		modelLife = glm::scale(modelLife, glm::vec3(lenghtCalcShot -0.02f, 0.01f, 0.15f));

		simpleShader.setMat4("model", modelLife);

		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

}
void player::drawLifePlayer(Shader simpleShader) {

	simpleShader.use();

	float offSet = 0.0f;

	if (life != lifeMax) {
		 offSet = ((lifeMax - life) / 2)/lifeMax;
	}

	float lifeLenght = life / lifeMax;

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureLife);
	glBindVertexArray(cubeVAO);

	//lightShader.setVec3("colorcube", 1.0f, 0.0f, 0.0f);
	glm::mat4 modelLife = glm::mat4(1.0f);

	modelLife = glm::translate(modelLife, glm::vec3(x - offSet, y + 2.5f, z));
	modelLife = glm::rotate(modelLife, 3.14f / 2.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	modelLife = glm::translate(modelLife, glm::vec3(0.0f, 0.0f, 0.0f));
	modelLife = glm::scale(modelLife, glm::vec3(lifeLenght, 0.01f, 0.25f));

	simpleShader.setMat4("model", modelLife);

	glDrawArrays(GL_TRIANGLES, 0, 36);

}