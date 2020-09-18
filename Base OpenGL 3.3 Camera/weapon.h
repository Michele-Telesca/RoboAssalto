#pragma once
#include "point3D.h"
#include "weapon.h"

class weapon {

public:

	weapon() {};
	//costruttore per tutte le armi
	weapon(float lengthRange, float angleRange, float lengthBase) : angleRange(angleRange), lengthRange(lengthRange), lengthBase(lengthBase) {}

	float lengthRange; //lunghezza di mira
	float lengthBase;
	float angleRange; //apertura della mira

	void drawTarget(Shader myShader, float x, float y, float z, int texturePlayer, float angle); //disegna la mira... avrà bisogno della posizione del player e dalla direzione

	bool isShotArea(); //controlla se ci troviamo all'interno dell'area di mira
	void initWeapon();

};

//init arma iniziale
void weapon::initWeapon() {

	/*lengthRange = 4.0f;
	lengthBase = 2.0f;
	angleRange = 90.0f;*/

}

void weapon::drawTarget(Shader lightShader, float x, float y, float z, int texturePlayer, float angle) {

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texturePlayer);
	glBindVertexArray(cubeVAO);

	lightShader.setVec3("colorcube", 1.0f, 1.0f, 1.0f);
	glm::mat4 modelW = glm::mat4(1.0f);
	float dx = (lengthRange / 2.0f) * sin(angle);
	float dy = (lengthRange / 2.0f) * cos(angle);

	modelW = glm::translate(modelW, glm::vec3(dx + x, 1.1f, dy + z));
	modelW = glm::rotate(modelW, angle, glm::vec3(0.0f, 1.0f, 0.0f));
	modelW = glm::translate(modelW, glm::vec3(0.0f, 0.0f, 0.0f));
	modelW = glm::scale(modelW, glm::vec3(lengthBase, 0.01f, lengthRange));

	//cout << "*** weapon (X,Z): (" << x << ", " << z << ")" << endl;

	lightShader.setMat4("model", modelW);
	glDrawArrays(GL_TRIANGLES, 0, 36);

}

bool weapon::isShotArea() {
	return false;
}