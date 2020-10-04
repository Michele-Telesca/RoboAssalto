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

	bool destroyed;//true quando il colpo ha hittato un nemico o un oggetto... 
	bool isShot = false;

	void inizializza();
	void draw(Shader lightShader, int texturePlayer); //disegna il colpo in base al weapon 
	float direction;

	float getX() {
		return x;
	}

	float getZ() {
		return z;
	}

};

void playerShot::inizializza() {
	x = -1000.0f;
	z = -1000.0f;
	startX = -1000.0f;
	startZ = -1000.0f;
	y = 1.4f;
	direction = 0.0f;
	isShot = false;
	angle = 0.0f;
}

void playerShot::draw(Shader lightShader, int texturePlayer) {

	lightShader.use();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texturePlayer);
	glBindVertexArray(cubeVAO);

	lightShader.setVec3("colorcube", 1.0f, 0.0f, 0.0f);
	glm::mat4 modelW = glm::mat4(1.0f);

	modelW = glm::translate(modelW, glm::vec3(x, y, z));
	modelW = glm::rotate(modelW, angle, glm::vec3(0.0f, 1.0f, 0.0f));
	modelW = glm::scale(modelW, glm::vec3(SHOT_DIM, SHOT_DIM, SHOT_DIM));

	lightShader.setMat4("model", modelW);
	glDrawArrays(GL_TRIANGLES, 0, 36);


}

