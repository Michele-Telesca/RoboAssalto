#pragma once
#include "point3D.h"
#include "weapon.h"
#include "globalData.h"

class weapon {

public:

	weapon() {};

	weapon(int type) {
		weapon_type = type;	
	}

	float lengthRange; //lunghezza di mira
	float lengthBase;
	float angleRange; //apertura della mira

	int weapon_type; //WEAPON_SHOTGUN = 1; WEAPON_SNIPER = 2;

	void drawTarget(Shader simpleShader, float x, float y, float z, int texturePlayer, float angle); //disegna la mira... avrà bisogno della posizione del player e dalla direzione

	void setWeaponProperties();

};

//init arma iniziale
void weapon::setWeaponProperties() {

	if (weapon_type == WEAPON_SHOTGUN) {
		lengthRange = LENGTH_RANGE_SHOTGUN;
		angleRange = ANGLE_RANGE_SHOTGUN;
		lengthBase = LENGTH_BASE_SHOTGUN;
	}
	else if (weapon_type == WEAPON_SNIPER) {
		lengthRange = LENGTH_RANGE_SNIPER;
		angleRange = ANGLE_RANGE_SNIPER;
		lengthBase = LENGTH_BASE_SNIPER;
	}

}

void weapon::drawTarget(Shader simpleShader, float x, float y, float z, int texturePlayer, float angle) {

	simpleShader.use();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glActiveTexture(GL_TEXTURE0);

	glBindTexture(GL_TEXTURE_2D, texturePlayer);
	glBindVertexArray(cubeVAO);

	glm::mat4 modelW = glm::mat4(UNIT);
	float dx = (lengthRange / 2.0f) * sin(angle);
	float dy = (lengthRange / 2.0f) * cos(angle);

	modelW = glm::translate(modelW, glm::vec3(dx + x, y+0.015f, dy + z));
	modelW = glm::rotate(modelW, angle, glm::vec3(0.0f, UNIT, 0.0f));
	modelW = glm::translate(modelW, glm::vec3(0.0f, 0.0f, 0.0f));
	modelW = glm::scale(modelW, glm::vec3(lengthBase, 0.001f, lengthRange));

	simpleShader.setMat4("model", modelW);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	glDisable(GL_BLEND);

}

