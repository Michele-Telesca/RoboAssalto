#pragma once
#include "point3D.h"
#include "weapon.h"

class playerShot {

public:

	playerShot() {}

	float x; //punto in cui il colpo si trova
	float y;
	float z;

	float startX; //punto da cui è partito
	float startZ;
	float finishX;
	float finishZ;//punto massimo in cui arriva il colpo

	float angle;

	Model* shotModel;
	bool destroyed;//true quando il colpo ha hittato un nemico o un oggetto... 
	bool isShot = false;
	
	float damage; //danno del proiettile

	void inizializza();
	//void draw(Shader lightShader, int texturePlayer,float dim); //disegna il colpo in base al weapon 
	void drawPlayerShot(Shader simpleShader, int texturePlayer, weapon *wea); //disegna il colpo in base al weapon 
	float direction;

	float getX() {
		return x;
	}

	float getZ() {
		return z;
	}

	float setDemage(float dem) {
		damage = dem;
	}

};

void playerShot::inizializza() {
	x = -1000.0f;
	z = -1000.0f;
	startX = -1000.0f;
	startZ = -1000.0f;
	y = 1.8f;
	direction = 0.0f;
	isShot = false;
	angle = 0.0f;
	damage = SNIPER_DAMAGE;

	shotModel = new Model();
	shotModel->loadModel("models/shot/shot.dae");

}

//void playerShot::draw(Shader lightShader, int texturePlayer,float dim) {
void playerShot::drawPlayerShot(Shader simpleShader, int texturePlayer,weapon *wea) {


	simpleShader.use();

	// material properties
	simpleShader.setVec3("material.ambient", 0.9f, 0.9f, 0.9f);
	simpleShader.setVec3("material.diffuse", UNIT, UNIT, UNIT);
	simpleShader.setVec3("material.specular", UNIT, UNIT, UNIT);
	simpleShader.setFloat("material.shininess", 76.8f);

	if (wea->lengthBase != LENGTH_BASE_SHOTGUN) {

		glm::mat4 model = glm::mat4(UNIT);
		model = glm::translate(model, glm::vec3(x, y, z));
		model = glm::rotate(model, angle, glm::vec3(0.0f, UNIT, 0.0f));
		model = glm::scale(model, glm::vec3(0.015f, 0.015f, 0.20f)); //bullet scale
		simpleShader.setMat4("model", model);
		shotModel->Draw(simpleShader); //bullet draw
	}
	else {

		simpleShader.use();
		glm::mat4 model = glm::mat4(UNIT);
		model = glm::translate(model, glm::vec3(x - 0.5f, y, z));
		model = glm::rotate(model, angle, glm::vec3(0.0f, UNIT, 0.0f));
		model = glm::scale(model, glm::vec3(0.015f, 0.015f, 0.20f)); 
		simpleShader.setMat4("model", model);
		shotModel->Draw(simpleShader); 

		simpleShader.use();
		glm::mat4 model1 = glm::mat4(UNIT);
		model1 = glm::translate(model1, glm::vec3(x + 0.5f, y, z));
		model1 = glm::rotate(model1, angle, glm::vec3(0.0f, UNIT, 0.0f));
		model1 = glm::scale(model1, glm::vec3(0.015f, 0.015f, 0.20f));
		simpleShader.setMat4("model", model1);
		shotModel->Draw(simpleShader); 

		simpleShader.use();
		glm::mat4 model2 = glm::mat4(UNIT);
		model2 = glm::translate(model2, glm::vec3(x, y - 0.2f, z));
		model2 = glm::rotate(model2, angle, glm::vec3(0.0f, UNIT, 0.0f));
		model2 = glm::scale(model2, glm::vec3(0.015f, 0.015f, 0.20f));
		simpleShader.setMat4("model", model2);
		shotModel->Draw(simpleShader); 

		simpleShader.use();
		glm::mat4 model3 = glm::mat4(UNIT);
		model3 = glm::translate(model3, glm::vec3(x, y + 0.2f, z));
		model3 = glm::rotate(model3, angle, glm::vec3(0.0f, UNIT, 0.0f));
		model3 = glm::scale(model3, glm::vec3(0.015f, 0.015f, 0.015f));
		simpleShader.setMat4("model", model3);
		shotModel->Draw(simpleShader); 
	}
	
}

