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
	float lifeMax;
	int numShotsAvailable; //colpi a disposizione
	float chargingTime; //tempo di ricarica del colpo
	float timeLastShot; //tempo dell'ultimo colpo. servirà in update per calcolare se è passato abbastanza tempo per ricaricare  
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
	weapon* wea = new weapon(3.0f, 90.0f, 2.0f); //arma posseduta al momento

	//lista colpi
	vector<playerShot*> listShot;

	//texture
	unsigned int texture1;
	unsigned int textureLife;
	unsigned int textureShotBar;

	//prototipi
	void drawPlayer(Shader animShader, Shader lightShader, glm::mat4 view, glm::vec3 mousePoint); //disegna il player
	void animatePlayer(Shader animShader);
	void initPlayer(); //inizializza il player
	void updateAngleShot(float tempDegree, float anglePlayer);
	bool checkShotIsAvaiable(float currentTime);
	void drawLifePlayer(Shader lightShader);

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

void player::initPlayer() {

	//punto in cui nasce
	x = 0.0f;
	y = 0.5f;
	z = 0.0f;

	anglePlayer = 0.0f;

	//vita iniziale
	life= 100;
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
	meshRunning.loadMesh("animation/player_michelle/shotgun_running/shotgun_running.dae");
	meshStanding.loadMesh("animation/player_michelle/shotgun_standing/shotgun_standing.dae");

	// tempo per le animazioni
	animationTime_playerStanding = 0.0f;
	animationTime_playerRunning = 0.0f;

}

float angleBetween(const glm::vec3 a, const glm::vec3 b) {

	float angle = atan2(b.x, a.x) - atan2(b.z, a.y);
	return angle;
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
	//se i colpi disponibili sono minori di 0 non posso sparare
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

	}

	//model
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(x, 0.5f, z));
	model = glm::rotate(model, radiansAngle, glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f)); //per metterlo in posizione verticale sul pavimento
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
	animShader.setMat4("model", model);	

	animatePlayer(animShader); //animazione
	float currentTime = glfwGetTime();
	//controllo la lista dei colpi e ne setto gli angoli 
	bool shotIsAvaiable = checkShotIsAvaiable(currentTime);
	

	//cout << "*** Shot: " << numShotsAvailable << ")" << endl;
	
	if (startPlayerShot) {
		if (shotIsAvaiable) {
			listShot[numShotsAvailable - 1]->startX = x; //posizione x del player
			listShot[numShotsAvailable - 1]->startZ = z; //posizione z del player
			listShot[numShotsAvailable - 1]->angle = angleWeapon;
			listShot[numShotsAvailable - 1]->isShot = true;

			removeShot();

		}
		startPlayerShot = false;
	}

	if (mouseSxIsSelected) {
		wea->drawTarget(lightShader, view, x, y, z, texture1, angleWeapon);
	}

	// material properties
	lightShader.setVec3("material.ambient", 1.0f, 1.0f, 1.0f);
	lightShader.setVec3("material.diffuse", 1.0f, 1.0f, 1.0f);
	lightShader.setVec3("material.specular", 1.0f, 1.0f, 1.0f);
	lightShader.setFloat("material.shininess", 76.8f);


	for (int i = 0; i < numShot; i++) {
		if (listShot[i]->isShot) {
			listShot[i]->draw(lightShader, texture1);
		}
	}

	drawLifePlayer(lightShader);

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

void player::drawLifePlayer(Shader lightShader) {

	float offSet = 0.0f;

	if (life != lifeMax) {
		 offSet = ((lifeMax - life) / 2)/lifeMax;
	}

	lightShader.use();
	float lifeLenght = life / lifeMax;

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureLife);
	glBindVertexArray(cubeVAO);

	lightShader.setVec3("colorcube", 1.0f, 0.0f, 0.0f);
	glm::mat4 modelLife = glm::mat4(1.0f);

	modelLife = glm::translate(modelLife, glm::vec3(x - offSet, y + 2.5f, z));
	modelLife = glm::rotate(modelLife, 3.14f / 2.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	modelLife = glm::translate(modelLife, glm::vec3(0.0f, 0.0f, 0.0f));
	modelLife = glm::scale(modelLife, glm::vec3(lifeLenght, 0.01f, 0.25f));

	lightShader.setMat4("model", modelLife);

	glDrawArrays(GL_TRIANGLES, 0, 36);

}