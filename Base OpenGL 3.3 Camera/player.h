#pragma once
#include "model.h"
#include "weapon.h"
#include "skinned_mesh.h"
#include "globalData.h"
#include "playerShot.h"
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

	int numShotsAvailable;  //colpi a disposizione
	float chargingTime;     //tempo di ricarica del colpo
	float timeLastShot;     //tempo dell'ultimo colpo. servirà in update per calcolare se è passato abbastanza tempo per ricaricare  
	float delayShotTime;
	bool delayShotIsFinished;
	float anglePlayer;

	bool mouseSxIsSelected = false;
	bool startPlayerShot = false;

	int playerSelected;

	// modelli 3D con scheletro e animazione
	SkinnedMesh bryce_meshRunning_shotgun;
	SkinnedMesh bryce_meshStanding_shotgun;
	SkinnedMesh bryce_meshRunning_sniper;
	SkinnedMesh bryce_meshStanding_sniper;

	SkinnedMesh michelle_meshRunning_shotgun;
	SkinnedMesh michelle_meshStanding_shotgun;
	SkinnedMesh michelle_meshRunning_sniper;
	SkinnedMesh michelle_meshStanding_sniper;

	// tempo per le animazioni
	float animationTime_playerStanding;
	float animationTime_playerRunning;
	
	// target dell'arma
	weapon* wea;  //arma posseduta al momento

	//lista colpi
	vector<playerShot*> listShot;

	//texture
	unsigned int texture_target;
	unsigned int textureLife;
	unsigned int textureShotBar;
	unsigned int textureShadow;

	//prototipi
	void drawPlayer(Shader animShader, Shader simpleShader, glm::vec3 mousePoint, Shader lightShader); //disegna il player
	void animatePlayer(Shader animShader);
	void initPlayer(int selectedPlayer, int weaponType); //inizializza il player
	void updateAngleShot(float tempDegree, float anglePlayer);
	bool checkShotIsAvaiable(float currentTime);
	void drawLifePlayer(Shader lightShader);
	void drawChestLife(Shader lightShader);
	void drawShotAvaiable(int numShotsAvailable, float currentTime, Shader lightShader);
	bool checkShotDelay(float currentTime);
	void resetPlayer(int selectedPlayer, int weaponType);
	void loadMeshModel(int selectedPlayer);
	void drawShadowPlayer(Shader lightShader);

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
		numShotsAvailable = numShotsAvailable++;
	}

	void removeShot() {
		numShotsAvailable = numShotsAvailable--;
	}

	int getNumShot() {
		numShotsAvailable;
	}

};

void  player::resetPlayer(int selectedPlayer, int weaponType) {
	cout << "INIT selectedplayer: " << selectedPlayer << endl;

	playerSelected = selectedPlayer;
	cout << "ASSENGNATO: " << playerSelected << endl;

	wea = new weapon(weaponType);
	wea->setWeaponProperties();

	//punto in cui nasce
	x = PLAYER_SPOW_X;
	y = PLAYER_SPOW_Y;
	z = PLAYER_SPOW_Z;

	anglePlayer = 0.0f;

	//vita iniziale

	life = PLAYER_LIFE;
	chest_life = CHEST_LIFE;

	lifeMax = life;

	//numero colpi a disposizione
	setNumShotAvailable(numShot);

	//tempo ricarica colpo
	chargingTime = CHARGING_TIME;

	//tempo ultimo colpo
	timeLastShot = INIT_ZERO;

	//inizializzo la lista dei colpi
	for (int i = 0; i < numShot; i++) {
		playerShot* playerShot_i = new playerShot();
		listShot.push_back(playerShot_i);
		listShot[i]->inizializza();
	}

	// tempo per le animazioni
	animationTime_playerStanding = INIT_ZERO;
	animationTime_playerRunning = INIT_ZERO;

	delayShotTime = INIT_ZERO; //delay tra uno sparo e un altro
	delayShotIsFinished = true;
}

void player::loadMeshModel(int selectedPlayer) {

	michelle_meshRunning_shotgun.loadMesh("animation/player_michelle/shotgun_running/shotgun_running.dae");
	michelle_meshStanding_shotgun.loadMesh("animation/player_michelle/shotgun_standing/shotgun_standing.dae");
	michelle_meshRunning_sniper.loadMesh("animation/player_michelle/sniper_running/sniper_running.dae");
	michelle_meshStanding_sniper.loadMesh("animation/player_michelle/sniper_standing/sniper_standing.dae");

	bryce_meshRunning_shotgun.loadMesh("animation/player_bryce/shotgun_running/shotgun_running.dae");
	bryce_meshStanding_shotgun.loadMesh("animation/player_bryce/shotgun_standing/shotgun_standing.dae");
	bryce_meshRunning_sniper.loadMesh("animation/player_bryce/sniper_running/sniper_running.dae");
	bryce_meshStanding_sniper.loadMesh("animation/player_bryce/sniper_standing/sniper_standing.dae");

}

void player::initPlayer(int selectedPlayer, int weaponType) {
	cout << "INIT selectedplayer: " << selectedPlayer << endl;

	resetPlayer(selectedPlayer, weaponType);
	loadMeshModel(selectedPlayer);

}

float angleBetween(const glm::vec3 a, const glm::vec3 b) {

	float angle = atan2(b.x, a.x) - atan2(b.z, a.y);
	return angle;
}

bool player::checkShotDelay(float currentTime) { //tempo tra uno shot e un altro di file
	if (wea->weapon_type == WEAPON_SHOTGUN) {
		if (delayShotTime == INIT_ZERO || (currentTime - delayShotTime) > DELAY_SHOTGUN) {
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
	if (numShotsAvailable == MAX_SHOT_AVAILABLE) {
		setTimeLastShot(currentTime);
	}
	if (numShotsAvailable < MAX_SHOT_AVAILABLE) {
		if ((currentTime - timeLastShot) > chargingTime) {
			addNumShotAvailable();
			setTimeLastShot(currentTime);
			return true;
		}
	}
	//se i colpi disponibili sono minori di 0 non posso sparare oppure il tempo passato dal lastshot è inferiore a tot
	if (numShotsAvailable == MIN_SHOT_AVAILABLE) {
		return false;
	}
	//se ho colpi disponibili setto il tempo di lastShot e torno true
	//setTimeLastShot(currentTime);

	return true;
}

void player::updateAngleShot(float tempDegree, float anglePlayer) {

	for (float ang = ANGLE_0; ang < ANGLE_180; ang = ang + ANGLE_OFFSET) {
		float tempAng = ang + ANGLE_OFFSET;
		if (tempDegree >= ang && tempDegree < tempAng) {
			setAnglePlayer(ang);
		}
	}
	for (float ang = -ANGLE_180; ang < ANGLE_0; ang = ang + ANGLE_OFFSET) {
		float tempAng = ang + ANGLE_OFFSET;
		if (tempDegree >= ang && tempDegree < tempAng) {
			setAnglePlayer(ang + ANGLE_360);
		}
	}
}

void player::drawPlayer(Shader simpleShader, Shader animShader, glm::vec3 mousePoint,Shader lightShader) {
	
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
	glm::mat4 model = glm::mat4(UNIT);
	model = glm::translate(model, glm::vec3(x, PLAYER_SPOW_Y, z));
	model = glm::rotate(model, radiansAngle, glm::vec3(INIT_ZERO, UNIT, INIT_ZERO));
	model = glm::rotate(model, glm::radians(-ANGLE_PLAYER_ROTATE), glm::vec3(UNIT, INIT_ZERO, INIT_ZERO)); //per metterlo in posizione verticale sul pavimento
	model = glm::scale(model, glm::vec3(UNIT, UNIT, UNIT));
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

	// ----- OMBRA ------- //
	drawShadowPlayer(simpleShader);

	//DRAW TARGET
	if (mouseSxIsSelected) {
		wea->drawTarget(simpleShader, x, y, z, texture_target, angleWeapon);
	}

	//DRAW SHOT
	for (int i = FIRST_NAMBER; i < numShot; i++) {
		if (listShot[i]->isShot) {

				listShot[i]->drawPlayerShot(lightShader, texture_target, wea);
			
		}
	}

	

	//DRAW LIFE_INTERFACE

	drawLifePlayer(simpleShader);
	drawChestLife(simpleShader);

	//DRAW SHOT_INTERFACE
	drawShotAvaiable(numShotsAvailable, currentTime, simpleShader);
}

void player::drawShadowPlayer(Shader simpleShader) {

	simpleShader.use();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glActiveTexture(GL_TEXTURE0);

	glBindTexture(GL_TEXTURE_2D, textureShadow);
	glBindVertexArray(cubeVAO);

	//simpleShader.setVec3("colorcube", UNIT, 0.0f, 0.0f);
	glm::mat4 modelS = glm::mat4(UNIT);


	modelS = glm::translate(modelS, glm::vec3(x, y + SHADOW_OFFSET_Y_PLAYER, z));
	modelS = glm::rotate(modelS, HALF_PI, glm::vec3(INIT_ZERO, UNIT, INIT_ZERO));
	modelS = glm::translate(modelS, glm::vec3(INIT_ZERO, INIT_ZERO, INIT_ZERO));
	modelS = glm::scale(modelS, glm::vec3(SHADOW_SCALE_PLAYER, SHADOW_OFFSET_Y_PLAYER, SHADOW_SCALE_PLAYER));

	simpleShader.setMat4("model", modelS);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	glDisable(GL_BLEND);
}

void player::animatePlayer(Shader animShader) {

	vector <glm::mat4> transforms;

	if (moveDx == false && muoviSx == false && muoviSu == false && muoviGiu == false) { //se non mi muovo -> meshStanding
		if (wea->weapon_type == WEAPON_SHOTGUN) {
			if (playerSelected == PLAYER_MICHELLE) {
				michelle_meshStanding_shotgun.boneTransform(animationTime_playerStanding, transforms);
				glUniformMatrix4fv(glGetUniformLocation(animShader.ID, "bones"),
					transforms.size(),
					GL_FALSE,
					glm::value_ptr(transforms[0]));
				michelle_meshStanding_shotgun.render();
			}
			else if (playerSelected == PLAYER_BRYCE) {
				bryce_meshStanding_shotgun.boneTransform(animationTime_playerStanding, transforms);
				glUniformMatrix4fv(glGetUniformLocation(animShader.ID, "bones"),
					transforms.size(),
					GL_FALSE,
					glm::value_ptr(transforms[0]));
				bryce_meshStanding_shotgun.render();
			}

		}
		else if (wea->weapon_type == WEAPON_SNIPER) {
			if (playerSelected == PLAYER_MICHELLE) {
				michelle_meshStanding_sniper.boneTransform(animationTime_playerStanding, transforms);
				glUniformMatrix4fv(glGetUniformLocation(animShader.ID, "bones"),
					transforms.size(),
					GL_FALSE,
					glm::value_ptr(transforms[0]));
				michelle_meshStanding_sniper.render();
			}
			else if (playerSelected == PLAYER_BRYCE) {
				bryce_meshStanding_sniper.boneTransform(animationTime_playerStanding, transforms);
				glUniformMatrix4fv(glGetUniformLocation(animShader.ID, "bones"),
					transforms.size(),
					GL_FALSE,
					glm::value_ptr(transforms[0]));
				bryce_meshStanding_sniper.render();
			}

		}
		
	}
	else if (moveDx == true || muoviSx == true || muoviSu == true || muoviGiu == true) { //se mi muovo -> meshRunning		
		if (wea->weapon_type == WEAPON_SHOTGUN) {
			if (playerSelected == PLAYER_MICHELLE) {
				michelle_meshRunning_shotgun.boneTransform(animationTime_playerRunning, transforms);
				glUniformMatrix4fv(glGetUniformLocation(animShader.ID, "bones"),
					transforms.size(),
					GL_FALSE,
					glm::value_ptr(transforms[0]));
				michelle_meshRunning_shotgun.render();
			}
			else if (playerSelected == PLAYER_BRYCE) {
				bryce_meshRunning_shotgun.boneTransform(animationTime_playerRunning, transforms);
				glUniformMatrix4fv(glGetUniformLocation(animShader.ID, "bones"),
					transforms.size(),
					GL_FALSE,
					glm::value_ptr(transforms[0]));
				bryce_meshRunning_shotgun.render();
			}
		}
		else if (wea->weapon_type == WEAPON_SNIPER) {
			if (playerSelected == PLAYER_MICHELLE) {
				michelle_meshRunning_sniper.boneTransform(animationTime_playerRunning, transforms);
				glUniformMatrix4fv(glGetUniformLocation(animShader.ID, "bones"),
					transforms.size(),
					GL_FALSE,
					glm::value_ptr(transforms[0]));
				michelle_meshRunning_sniper.render();
			}
			else if (playerSelected == PLAYER_BRYCE) {
				bryce_meshRunning_sniper.boneTransform(animationTime_playerRunning, transforms);
				glUniformMatrix4fv(glGetUniformLocation(animShader.ID, "bones"),
					transforms.size(),
					GL_FALSE,
					glm::value_ptr(transforms[0]));
				bryce_meshRunning_sniper.render();
			}
		}
	}
}


//DRAW SHOT PLAYER
void player::drawShotAvaiable(int numShotsAvailable, float currentTime, Shader simpleShader) {


	float shotBarLenght = (lifeMax / MAX_SHOT_AVAILABLE) / lifeMax;
	float shotHalfBar = (shotBarLenght / 2.0);
	float center = x - shotBarLenght;

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	for (int i = 0; i < numShotsAvailable; i++) {



		simpleShader.use();


		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureShotBar);
		glBindVertexArray(cubeVAO);

		//lightShader.setVec3("colorcube", UNIT, 0.0f, 0.0f);
		glm::mat4 modelLife = glm::mat4(UNIT);

		modelLife = glm::translate(modelLife, glm::vec3(center + (shotBarLenght * i), y + OFFSET_SHOT_BAR, z));
		modelLife = glm::rotate(modelLife, HALF_PI, glm::vec3(UNIT, 0.0f, 0.0f));
		modelLife = glm::translate(modelLife, glm::vec3(0.0f, 0.0f, 0.0f));
		modelLife = glm::scale(modelLife, glm::vec3(shotBarLenght - SCALE_OFFSET_SHOT_BAR, SCALE_SHOT_BAR_Y, SCALE_SHOT_BAR_Z));

		simpleShader.setMat4("model", modelLife);

		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	if (numShotsAvailable < 3) {

		simpleShader.use();

		float lenghtCalcShot = ((currentTime - timeLastShot) * shotBarLenght) / chargingTime;

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture_target);
		glBindVertexArray(cubeVAO);

		glm::mat4 modelLife = glm::mat4(UNIT);


		float centerCalcStart = (center + (shotBarLenght * (numShotsAvailable))) - shotHalfBar;
		float centerCalc = centerCalcStart + (lenghtCalcShot / 2.0f);

		modelLife = glm::translate(modelLife, glm::vec3(centerCalc, y + OFFSET_SHOT_BAR, z));
		modelLife = glm::rotate(modelLife, HALF_PI, glm::vec3(UNIT, 0.0f, 0.0f));
		modelLife = glm::translate(modelLife, glm::vec3(0.0f, 0.0f, 0.0f));
		modelLife = glm::scale(modelLife, glm::vec3(lenghtCalcShot - SCALE_OFFSET_SHOT_BAR, SCALE_SHOT_BAR_Y, SCALE_SHOT_BAR_Z));

		simpleShader.setMat4("model", modelLife);

		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
	glDisable(GL_BLEND);
}

//DRAW LIFE PLAYER
void player::drawLifePlayer(Shader simpleShader) {

	glEnable(GL_BLEND);

	simpleShader.use();

	float offSet = 0.0f;

	if (life != lifeMax) {
		offSet = ((lifeMax - life) / 2) / lifeMax;
	}

	float lifeLenght = life / lifeMax;

	if (life < MIN_LIFE_PLAYER) {
		lifeLenght = MIN_LIFE_PLAYER;
	}

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureLife);
	glBindVertexArray(cubeVAO);

	//lightShader.setVec3("colorcube", UNIT, 0.0f, 0.0f);
	glm::mat4 modelLife = glm::mat4(UNIT);

	modelLife = glm::translate(modelLife, glm::vec3(x - offSet, y + OFFSET_POSITION_LIFEBAR, z));
	modelLife = glm::rotate(modelLife, HALF_PI, glm::vec3(UNIT, 0.0f, 0.0f));
	modelLife = glm::translate(modelLife, glm::vec3(0.0f, 0.0f, 0.0f));
	modelLife = glm::scale(modelLife, glm::vec3(lifeLenght, SCALE_SHOT_BAR_Y, SCALE_LIFEBARZ));

	simpleShader.setMat4("model", modelLife);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	glDisable(GL_BLEND);

}


void player::drawChestLife(Shader simpleShader) {

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	simpleShader.use();

	float offSet = 0.0f;

	if (chest_life != CHEST_LIFE) {
		offSet = ((CHEST_LIFE - chest_life) / 2) / CHEST_LIFE;
	}

	float lifeLenght = chest_life / CHEST_LIFE;

	if (chest_life < MIN_LIFE_CHEST) {
		lifeLenght = MIN_LIFE_CHEST;
	}

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureLife);
	glBindVertexArray(cubeVAO);

	//lightShader.setVec3("colorcube", UNIT, 0.0f, 0.0f);
	glm::mat4 modelLife = glm::mat4(UNIT);

	modelLife = glm::translate(modelLife, glm::vec3(-UNIT - offSet, y + OFFSET_Y_CHESTlIFE_BAR, 0.0f));
	modelLife = glm::rotate(modelLife, 3.14f / 2.0f, glm::vec3(UNIT, 0.0f, 0.0f));
	modelLife = glm::translate(modelLife, glm::vec3(0.0f, 0.0f, 0.0f));
	modelLife = glm::scale(modelLife, glm::vec3(lifeLenght, SCALE_SHOT_BAR_Y, SCALE_LIFEBARZ));

	simpleShader.setMat4("model", modelLife);

	glDrawArrays(GL_TRIANGLES, 0, 36);
	glDisable(GL_BLEND);

}