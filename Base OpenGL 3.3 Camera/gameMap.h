#pragma once
#include<stdio.h>
#include "game.h"
#include "operatore.h"

class gameMap {

public:

	unsigned int texturePrato;

	gameMap() {};

	void inizializza();

};

void gameMap::inizializza() {

	glm::vec3 pos(0.0f, 0.0f, 0.0f);		// Posizione camera
	glm::vec3 at(0.0f, 0.0f, -10.0f);		// Punto in cui "guarda" la camera
	glm::vec3 up(0.0f, 1.0f, 0.0f);			// Vettore up...la camera è sempre parallela al piano

	// ---- FLOOR ---- //
	for (float i = -50; i <= 50; i = i + 0.5) {
		for (float j = 50; j >= -50; j = j - 0.5) {

			// setto la texture
			myShader->setInt("myTexture1", 0);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texturePrato);
			glBindVertexArray(cubeVAO);

			//setto la view
			glm::mat4 view = glm::lookAt(pos, at, up);
			myShader->setMat4("view", view);

			//setto il colore
			myShader->setVec3("colorcube", 1.0f, 1.0f, 1.0f); //bianco (colore neutro)
 
			//creo il cubo
			operatore* tile = new operatore(0.5, 0.0f, 1.0f, 0.0f, 0.0f, i, -2.0, j, myShader);
			tile->drawCube();
		}
	}

}